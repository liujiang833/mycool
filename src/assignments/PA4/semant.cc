

#include "semant.h"

#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>

#include <string>

#include "utilities.h"

extern int semant_debug;
extern char* curr_filename;
std::unordered_map<Symbol, ClassNodeP> class_table;
std::unordered_map<Symbol, SymbolTableP> class_level_tables;
//////////////////////////////////////////////////////////////////////
//
// Symbols
//
// For convenience, a large number of symbols are predefined here.
// These symbols include the primitive type and method names, as well
// as fixed names used by the runtime system.
//
static Symbol
    arg,
    arg2,
    Bool,
    concat,
    cool_abort,
    copy,
    Int,
    in_int,
    in_string,
    IO,
    length,
    Main,
    main_meth,
    No_class,
    No_type,
    Object,
    out_int,
    out_string,
    prim_slot,
    self,
    SELF_TYPE,
    Str,
    str_field,
    substr,
    type_name,
    val;
//////////////////////////////////////////////////////////////////////
//
// Initializing the predefined symbols.
//
static void initialize_constants(void) {
    arg = idtable.add_string("arg");
    arg2 = idtable.add_string("arg2");
    Bool = idtable.add_string("Bool");
    concat = idtable.add_string("concat");
    cool_abort = idtable.add_string("abort");
    copy = idtable.add_string("copy");
    Int = idtable.add_string("Int");
    in_int = idtable.add_string("in_int");
    in_string = idtable.add_string("in_string");
    IO = idtable.add_string("IO");
    length = idtable.add_string("length");
    Main = idtable.add_string("Main");
    main_meth = idtable.add_string("main");
    //   _no_class is a symbol that can't be the name of any
    //   user-defined class.
    No_class = idtable.add_string("_no_class");
    No_type = idtable.add_string("_no_type");
    Object = idtable.add_string("Object");
    out_int = idtable.add_string("out_int");
    out_string = idtable.add_string("out_string");
    prim_slot = idtable.add_string("_prim_slot");
    self = idtable.add_string("self");
    SELF_TYPE = idtable.add_string("SELF_TYPE");
    Str = idtable.add_string("String");
    str_field = idtable.add_string("_str_field");
    substr = idtable.add_string("substr");
    type_name = idtable.add_string("type_name");
    val = idtable.add_string("_val");
}

ClassTable::ClassTable(Classes classes) : semant_errors(0), error_stream(cerr) {
    install_classes(classes);
    ClassNodeP object_node = class_table[Object];
    build_class_level_table(object_node);
    check_scope_and_type();
    check_main();
}

ClassTable::~ClassTable() {
    //free allocated nodes, though might not be necessary
    for (auto symbol_node : class_table) {
        ClassNodeP node = symbol_node.second;
        delete node;
    }
}

void ClassTable::check_main(){
    if(class_table.find(Main) == class_table.end()){
        fprintf(stderr,"Class Main is not defined.\n");
        semant_error();
        throw -1;
    }
    auto main_table = class_level_tables[Main];
    if(main_table->look_up_method(main_meth).type == nullptr){
        fprintf(stderr, "main method not found\n");
        semant_error();
        throw -1;
    }
}
void ClassTable::install_classes(Classes classes) {
    classes = add_basic_classes(classes);
    std::vector<ClassNodeP> class_nodes;
    for (int i = classes->first(); classes->more(i); i = classes->next(i)) {
        class__class* curr_class = (class__class*)classes->nth(i);
        // std::cout << curr_class->name << std::endl;
        //handle redefinition of a class
        if (class_table.find(curr_class->name) != class_table.end()) {
            fprintf(stderr, "%s:%d: redefinition of class %s\n", curr_class->get_filename()->get_string(), curr_class->get_line_number(), curr_class->name->get_string());
            semant_error();
            throw -1;
        }
        if(curr_class->name == SELF_TYPE){
            fprintf(stderr, "%s:%d: SELF_TYPE is not a valid class name\n",curr_class->get_filename()->get_string(), curr_class->get_line_number());
            semant_error();
            throw -1;
        }
        ClassNodeP node = new ClassNode(curr_class);
        class_nodes.push_back(node);
        class_table[curr_class->name] = node;
    }
    std::unordered_set<Symbol> uninheritables{Int, Bool, Str,SELF_TYPE};
    for (ClassNodeP node : class_nodes) {  //note: class_nodes only contains user defined classes
        Symbol parent_symbol = node->value->parent;
        char* filename = node->value->get_filename()->get_string();
        if (parent_symbol != No_class) {  //if a class has a parent class
            if (class_table.find(parent_symbol) != class_table.end()) {
                if (uninheritables.find(parent_symbol) == uninheritables.end()) {
                    node->parent = class_table[parent_symbol];
                    class_table[parent_symbol]->children.push_back(node);
                } else {
                    fprintf(stderr, "%s:%d: class %s is not inheritable\n",filename,node->value->get_line_number(), parent_symbol->get_string());
                    semant_error();
                    throw -1;
                }
            } else {
                fprintf(stderr, "%s:%d: class %s inherits non-existing class %s\n",filename ,node->value->get_line_number(), node->value->name->get_string(), parent_symbol->get_string());
                semant_error();
                throw -1;
            }
        } else if (node->value->name != Object) {
            //if the class doesn't have a parent class, we just make Object its parent class
            node->parent = class_table[Object];
            class_table[Object]->children.push_back(node);
        }
    }
    // dfs to check if there is a cycle in the inheritance graph
    std::unordered_set<ClassNodeP> visited;
    for (auto s_c : class_table) {
        cycle_dfs(s_c.second, visited);
    }
}

void ClassTable::cycle_dfs(ClassNodeP root, std::unordered_set<ClassNodeP>& visited) {
    if (visited.find(root) != visited.end()) {
        fprintf(stderr, "A cycle detected in class inheritance\n");
        fprintf(stderr, "%s", root->value->name->get_string());
        ClassNodeP curr = root->parent;
        while (curr != root) {
            fprintf(stderr, "<-%s", curr->value->name->get_string());
            curr = curr->parent;
        }
        throw -1;
    }
    visited.insert(root);
    for (ClassNodeP child : root->children) {
        cycle_dfs(child, visited);
    }
    visited.erase(root);
}
Classes ClassTable::add_basic_classes(Classes classes) {
    // The tree package uses these globals to annotate the classes built below.
    // curr_lineno  = 0;
    Symbol filename = stringtable.add_string("<basic class>");

    // The following demonstrates how to create dummy parse trees to
    // refer to basic Cool classes.  There's no need for method
    // bodies -- these are already built into the runtime system.

    // IMPORTANT: The results of the following expressions are
    // stored in local variables.  You will want to do something
    // with those variables at the end of this method to make this
    // code meaningful.

    //
    // The Object class has no parent class. Its methods are
    //        abort() : Object    aborts the program
    //        type_name() : Str   returns a string representation of class name
    //        copy() : SELF_TYPE  returns a copy of the object
    //
    // There is no need for method bodies in the basic classes---these
    // are already built in to the runtime system.

    Class_ Object_class =
        class_(Object,
               No_class,
               append_Features(
                   append_Features(
                       single_Features(method(cool_abort, nil_Formals(), Object, no_expr())),
                       single_Features(method(type_name, nil_Formals(), Str, no_expr()))),
                   single_Features(method(copy, nil_Formals(), SELF_TYPE, no_expr()))),
               filename);
    classes = append_Classes(single_Classes(Object_class), classes);
    //
    // The IO class inherits from Object. Its methods are
    //        out_string(Str) : SELF_TYPE       writes a string to the output
    //        out_int(Int) : SELF_TYPE            "    an int    "  "     "
    //        in_string() : Str                 reads a string from the input
    //        in_int() : Int                      "   an int     "  "     "
    //
    Class_ IO_class =
        class_(IO,
               Object,
               append_Features(
                   append_Features(
                       append_Features(
                           single_Features(method(out_string, single_Formals(formal(arg, Str)),
                                                  SELF_TYPE, no_expr())),
                           single_Features(method(out_int, single_Formals(formal(arg, Int)),
                                                  SELF_TYPE, no_expr()))),
                       single_Features(method(in_string, nil_Formals(), Str, no_expr()))),
                   single_Features(method(in_int, nil_Formals(), Int, no_expr()))),
               filename);
    classes = append_Classes(single_Classes(IO_class), classes);
    //
    // The Int class has no methods and only a single attribute, the
    // "val" for the integer.
    //
    Class_ Int_class =
        class_(Int,
               Object,
               single_Features(attr(val, prim_slot, no_expr())),
               filename);
    classes = append_Classes(single_Classes(Int_class), classes);
    //
    // Bool also has only the "val" slot.
    //
    Class_ Bool_class =
        class_(Bool, Object, single_Features(attr(val, prim_slot, no_expr())), filename);
    classes = append_Classes(single_Classes(Bool_class), classes);
    //
    // The class Str has a number of slots and operations:
    //       val                                  the length of the string
    //       str_field                            the string itself
    //       length() : Int                       returns length of the string
    //       concat(arg: Str) : Str               performs string concatenation
    //       substr(arg: Int, arg2: Int): Str     substring selection
    //
    Class_ Str_class =
        class_(Str,
               Object,
               append_Features(
                   append_Features(
                       append_Features(
                           append_Features(
                               single_Features(attr(val, Int, no_expr())),
                               single_Features(attr(str_field, prim_slot, no_expr()))),
                           single_Features(method(length, nil_Formals(), Int, no_expr()))),
                       single_Features(method(concat,
                                              single_Formals(formal(arg, Str)),
                                              Str,
                                              no_expr()))),
                   single_Features(method(substr,
                                          append_Formals(single_Formals(formal(arg, Int)),
                                                         single_Formals(formal(arg2, Int))),
                                          Str,
                                          no_expr()))),
               filename);
    classes = append_Classes(single_Classes(Str_class), classes);
    return classes;
}

void ClassTable::build_class_level_table(ClassNodeP class_node) {
    // std::cout << class_node->value->name << "\n";
    SymbolTableP class_table = new SymbolTable(class_node->value->name);
    class_table->class_name = class_node->value->name;
    if (class_node->parent != nullptr) {
        class_table->parent_table = class_level_tables[class_node->parent->value->name];
    }
    class_level_tables[class_node->value->name] = class_table;
    class_table->is_class_level = true;
    class__class* ast_node = class_node->value;
    Features features = ast_node->features;
    for (int i = features->first(); features->more(i); i = features->next(i)) {
        Feature feature = features->nth(i);
        // std::cout << typeid(*feature).name() << std::endl;
        if (typeid(*feature) == typeid(method_class)) {
            //we now know the feature is actually a method definition
            add_method((method_class*)feature, class_table, ast_node->get_filename()->get_string());
        } else {
            //if a feature is not a method, then it must be an attribute
            add_attr((attr_class*)feature, class_table, ast_node->get_filename()->get_string());
        }
    }
    for (auto child : class_node->children) {
        build_class_level_table(child);
    }
}

void ClassTable::add_attr(attr_class* attr, SymbolTableP symbol_table, char* filename) {
    if (attr->name == idtable.add_string("self")) {
        fprintf(stderr, "%s:%d: self is not a valid name for object\n", filename, attr->get_line_number());
        semant_error();
        return;
    }

    if (symbol_table->look_up_object(attr->name).type != nullptr) {
        fprintf(stderr, "%s:%d: redefinition of attribute %s\n", filename, attr->get_line_number(), attr->name->get_string());
        semant_error();
        return;
    }
    symbol_table->add_object(attr->name, (attr->type_decl));
}

void ClassTable::add_method(method_class* method, SymbolTableP symbol_table, char* filename) {
    //Note: formals are corrected in place.
    check_and_remedy(method->formals,filename);
    if (symbol_table->methods.find(method->name) != symbol_table->methods.end()) {
        fprintf(stderr, "%s:%d: redefinition of method %s\n", filename, method->get_line_number(), method->name->get_string());
        semant_error();
        return;
    }
    Info inherited = symbol_table->look_up_method(method->name);
    if (inherited.type != nullptr) {
        Formals inherited_formals = symbol_table->look_up_method(method->name).formals;
        if (inherited.type != method->return_type) {
            fprintf(stderr, "%s:%d: method %s has different return type than the method it overrites\n", filename, method->get_line_number(), method->name->get_string());
            semant_error();
            return;
        }
        if (!same_formal(method->formals, inherited_formals)) {
            fprintf(stderr, "%s:%d: method %s has different parameter types than the method it overrites\n", filename, method->get_line_number(), method->name->get_string());
            semant_error();
            return;
        }
    }
    std::unordered_set<Symbol> visited;
    for(int i=method->formals->first(); method->formals->more(i); i=method->formals->next(i)){
        auto formal = (formal_class*) method->formals->nth(i);
        if(formal->name == idtable.add_string("self")){
            fprintf(stderr, "%s:%d: self can't be used as the name for a formal\n",filename,method->get_line_number());
            semant_error();
            return;
        }
        if(visited.find(formal->name) != visited.end()){
            fprintf(stderr, "%s:%d: duplicated formal %s\n",filename, method->get_line_number(),formal->name->get_string());
            semant_error();
            return;
        }
        visited.insert(formal->name);
    } 
    symbol_table->add_method(method->name,Info(method->return_type, method->formals));
}

void ClassTable::check_and_remedy(Formals formals,char* filename) {
    for (int i = formals->first(); formals->more(i); i = formals->next(i)) {
        formal_class* formal = (formal_class*)formals->nth(i);
        if (class_table.find(formal->type_decl) == class_table.end()) {
            fprintf(stderr, "%s:%d: parameter %s has invalid type\n",filename ,formal->get_line_number(), formal->type_decl->get_string());
            semant_error();
            // remedy the type object so we can keep doing semantic analysis
            formal->type_decl = Object;
        }
    }
}

bool ClassTable::same_formal(Formals a, Formals b) {
    if (a->len() != b->len())
        return false;
    for (int i = a->first(), j = b->first(); a->more(i); i = a->next(i), j = b->next(j)) {
        formal_class* a_formal = (formal_class*)a->nth(i);
        formal_class* b_formal = (formal_class*)b->nth(j);
        if (a_formal->type_decl != b_formal->type_decl)
            return false;
    }
    return true;
}

void ClassTable::check_scope_and_type() {
    auto root = class_table[Object];
    check_scope_and_type_r(root);
}

void ClassTable::check_scope_and_type_r(ClassNodeP root) {
    static std::unordered_set<Symbol> basic_classes{Object, Bool, Int, Str, IO};
    if (basic_classes.find(root->value->name) == basic_classes.end()) {
        semant_errors +=  root->value->check_and_annotate(class_level_tables[root->value->name],root->value->get_filename()->get_string());
    }
    for (auto child : root->children) {
        check_scope_and_type_r(child);
    }
}
////////////////////////////////////////////////////////////////////
//
// semant_error is an overloaded function for reporting errors
// during semantic analysis.  There are three versions:
//
//    ostream& ClassTable::semant_error()
//
//    ostream& ClassTable::semant_error(Class_ c)
//       print line number and filename for `c'
//
//    ostream& ClassTable::semant_error(Symbol filename, tree_node *t)
//       print a line number and filename
//
///////////////////////////////////////////////////////////////////

ostream& ClassTable::semant_error(Class_ c) {
    return semant_error(c->get_filename(), c);
}

ostream& ClassTable::semant_error(Symbol filename, tree_node* t) {
    error_stream << filename << ":" << t->get_line_number() << ": ";
    return semant_error();
}

ostream& ClassTable::semant_error() {
    semant_errors++;
    return error_stream;
}

/*   This is the entry point to the semantic checker.

     Your checker should do the following two things:

     1) Check that the program is semantically correct
     2) Decorate the abstract syntax tree with type information
        by setting the `type' field in each Expression node.
        (see `tree.h')

     You are free to first do 1), make sure you catch all semantic
     errors. Part 2) can be done in a second stage, when you want
     to build mycoolc.
 */
void program_class::semant() {
    initialize_constants();

    /* ClassTable constructor may do some semantic analysis */
    // In my design it does all the semantic analysis
    try {
        ClassTableP t = new ClassTable(classes);
        if (t->errors() > 0)
            throw -1;
    } catch (int e) {
        cerr << "Compilation halted due to static semantic errors." << endl;
        exit(1);
    }
}

Info SymbolTable::look_up_method(Symbol name) {
    if (methods.find(name) != methods.end()) {
        return methods[name];
    }

    if (parent_table != nullptr) {
        return parent_table->look_up_method(name);
    }

    return Info();
}
Info SymbolTable::look_up_object(Symbol name) {
    if (objects.find(name) != objects.end()) {
        return objects[name];
    }

    if (parent_table != nullptr) {
        return parent_table->look_up_object(name);
    }

    return Info();
}
void SymbolTable::add_object(Symbol name, Info&& info) {
    objects[name] = info;
}
void SymbolTable::add_method(Symbol name, Info&& info) {
    methods[name] = info;
}

Symbol SymbolTable::get_self_type(){
    if(class_name != nullptr){
        return class_name;
    }
    assert(parent_table != nullptr);
    return parent_table->get_self_type();
}