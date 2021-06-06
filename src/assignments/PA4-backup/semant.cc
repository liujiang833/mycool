

#include "semant.h"

#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>

#include <algorithm>
#include <typeinfo>

#include "utilities.h"

extern int semant_debug;
extern char *curr_filename;

//////////////////////////////////////////////////////////////////////
//
// Symbols
//
// For convenience, a large number of symbols are predefined here.
// These symbols include the primitive type and method names, as well
// as fixed names used by the runtime system.
//
//////////////////////////////////////////////////////////////////////
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

Symbol SymbolTable::not_a_symbol = idtable.add_string("_not_a_symbol");
std::unordered_map<Symbol, std::unordered_map<Symbol, SymbolData>> SymbolTable::global_methods;
std::unordered_map<Symbol, std::unordered_map<Symbol, SymbolData>> SymbolTable::global_objects;
std::unordered_map<Symbol, SymbolData> SymbolTable::global_classes;
void ClassTable::build_global_table() {
    for (ClassNode *node : class_nodes) {
        class__class *one_class = node->value;
        SymbolData self_data(SymbolType::attribute_type);
        SymbolTable::global_objects[one_class->name][idtable.add_string("self")] = self_data;
        SymbolTable::global_classes[one_class->name] = SymbolData(SymbolType::class_type);
        Features features = one_class->features;
        for (int j = features->first(); features->more(j); j = features->next(j)) {
            Feature f = features->nth(j);
            if (typeid(*f) == typeid(method_class)) {  //the actual type of feature is method_class
                method_class *method = static_cast<method_class *>(f);
                auto& method_table = SymbolTable::global_methods[one_class->name];
                // we don't allow redefinition of a method within a single class
                if(method_table.find(method->name) != method_table.end()){
                    fprintf(stderr, "Line %d: Method %s has already been defined\n",method->get_line_number(),method->name->get_string());
                    semant_error();
                }else{
                    auto& parent_table = SymbolTable::global_methods[node->parent->value->name];
                    if(parent_table.find(method->name) != parent_table.end()){
                        auto& parent_method = parent_table[method->name];
                        auto parent_formals = parent_method.formals;
                        auto current_formals = method->formals;
                        bool error_f = false;
                        if(parent_formals->len() != current_formals->len()){
                            error_f = true;
                        } else{
                            for(int i = parent_formals->first(), j = current_formals->first();
                                    parent_formals->more(i); i= parent_formals->next(i), j=current_formals->next(j)){
                                auto p_formal = static_cast<formal_class*>(parent_formals->nth(i));
                                auto c_formal = static_cast<formal_class*>(current_formals->nth(j));
                                if(p_formal->type_decl != c_formal->type_decl){
                                    error_f = true;
                                    break;
                                }
                            }
                        }
                        if(error_f){
                            fprintf(stderr, "Line %d: Method %s has already different parameter types as its parent\n",method->get_line_number(),method->name->get_string());
                            semant_error();
                        }
                    }
                    //add the definition to symbol table for the class
                    SymbolData data(SymbolType::method_type);
                    data.return_type = method->return_type;
                    data.formals = method->formals;
                    data.return_type = method->return_type;
                    SymbolTable::global_methods[one_class->name][method->name] = data;
                }
            } else if (typeid(*f) == typeid(attr_class)) {  //the actural type of feature is attr_class
                attr_class *attribute = static_cast<attr_class *>(features->nth(j));
                SymbolData attr_data = SymbolData(SymbolType::attribute_type);
                attr_data.return_type = attribute->type_decl;
                auto &attr_table = SymbolTable::global_objects[one_class->name];
                if (attr_table.find(attribute->name) == attr_table.end()) {  //handle redefinition of attributes
                    SymbolTable::global_objects[one_class->name][attribute->name] = attr_data;
                } else {
                    fprintf(stderr, "Line %d: Attribute %s has already been defined\n", attribute->get_line_number(), attribute->name->get_string());
                    semant_error();
                }
            } else {
                fprintf(stderr, "Feature is neither a method nor an attribute\n");
                exit(1);
            }
        }
    }
    SymbolTable::dump_global(std::cout);
}

void ClassTable::topo_sort() {
    class_nodes = std::vector<ClassNode *>();
    add_nodes(class_nodes, object_node);
}
void ClassTable::add_nodes(std::vector<ClassNode *> &nodes, ClassNode *root) {
    nodes.push_back(root);
    for (auto child : root->children) {
        add_nodes(nodes, child);
    }
}
void SymbolTable::add_object(Symbol symbol, SymbolData data) {
    objects[symbol] = data;
}
SymbolData &SymbolTable::look_up_object(Symbol symbol) {
    if (objects.find(symbol) != objects.end()) {
        return objects[symbol];
    }

    if (parent != nullptr) {
        return parent->look_up_object(symbol);
    }
    return objects[not_a_symbol];
}

SymbolData &SymbolTable::look_up_method_self(Symbol symbol) {
    if (methods.find(symbol) != methods.end()) {
        return methods[symbol];
    }

    if (parent != nullptr) {
        return parent->look_up_method_self(symbol);
    }
    return methods[not_a_symbol];
}
SymbolData &SymbolTable::look_up_class(Symbol symbol) {
    if (global_classes.find(symbol) != global_classes.end()) {
        return global_classes[symbol];
    }
    return global_classes[not_a_symbol];
}
SymbolData &SymbolTable::look_up_method(Symbol symbol, Symbol class_) {
    if (global_methods.find(class_) == global_methods.end())
        return global_classes[not_a_symbol];
    std::unordered_map<Symbol, SymbolData> &class_to_method = global_methods[class_];
    if (class_to_method.find(symbol) != class_to_method.end()) {
        return global_classes[symbol];
    }
    return global_classes[not_a_symbol];
}
std::string SymbolTable::pad(int n) {
    static std::string padding = std::string(512, ' ').c_str();
    return padding.substr(0, n);
}
ostream &SymbolTable::dump_global(ostream &os) {
    os << "global class table:\n";
    for (auto class_ : global_classes) {
        os << pad(4) << class_.first->get_string() << "\n";
    }

    os << "global object table:\n";
    for (auto class_object : global_objects) {
        os << pad(4) << "class " << class_object.first->get_string() << ": \n";
        for (auto data : class_object.second) {
            os << pad(8) << data.first->get_string() << "\n";
        }
    }
    os << "global method table:\n";
    for (auto class_method : global_methods) {
        os << pad(4) << "class " << class_method.first->get_string() << ": \n";
        for (auto data : class_method.second) {
            os << pad(8) << data.first->get_string() << "\n";
        }
    }
    return os;
}
ostream &SymbolTable::dump(ostream &os) {
    os << "local object table:\n";
    for (auto object : objects) {
        os << pad(4) << object.first->get_string() << "\n";
    }

    return os;
}

int SymbolTable::dump_methods(ostream &os) {
    int padding = 0;
    if (parent != nullptr) {
        padding = parent->dump_methods(os);
    }
    int more_pad = 4;
    padding += more_pad;
    os << pad(padding) << "layer " << padding / 4 << "\n";
    for (auto pair : methods) {
        os << pad(padding) << pair.first->get_string() << "\n";
    }
    return padding;
}

int SymbolTable::dump_objects(ostream &os) {
    int padding = 0;
    if (parent != nullptr) {
        padding = parent->dump_objects(os);
    }
    int more_pad = 4;
    padding += more_pad;
    os << pad(padding) << "layer " << padding / 4 << "\n";
    for (auto pair : objects) {
        os << pad(padding) << pair.first->get_string() << "\n";
    }
    return padding;
}
bool ClassNode::is_parent(ClassNode *other) {
    return strcmp(other->parent_name, this->class_name) == 0;
}

ClassTable::ClassTable(Classes classes) : semant_errors(0), error_stream(cerr) {
    this->classes = classes;
    install_basic_classes();
    build_tree();
    std::vector<ClassNode *> track_stack;
    check_cycle(object_node, track_stack);
    build_global_table();
    check_scope_and_type();
    free_tree();
    // SymbolTable::dump_global(std::cout);
    // exit(1);
}
void ClassTable::build_tree() {
    //gather all class names
    for (int i = classes->first(); classes->more(i); i = classes->next(i)) {
        class__class *one_class = static_cast<class__class *>(classes->nth(i));
        ClassNode *node = new ClassNode(one_class->name->get_string(), one_class);
        node->parent_name = one_class->parent->get_string();
        class_nodes.push_back(node);
    }
    //find Object class
    auto it = class_nodes.begin();
    for (ClassNode *node : class_nodes) {
        if (strcmp(node->class_name, Object->get_string()) == 0) {
            object_node = node;
            break;
        }
        it++;
    }
    //get rid of Object class, from class name list
    class_nodes.erase(it);
    //build class dependency graph
    for (ClassNode *child_class : class_nodes) {
        bool parent_defined = false;
        for (ClassNode *parent_class : class_nodes) {
            if (parent_class->is_parent(child_class)) {
                parent_class->children.push_back(child_class);
                child_class->parent = parent_class;
                parent_defined = true;
            }
        }
        //make sure we don't find the parent class when a class inherits Object
        if (strcmp(child_class->parent_name, Object->get_string()) == 0) {
            parent_defined = true;
        }
        //we always add a class to the children of Object class
        object_node->children.push_back(child_class);
        if(child_class->parent == nullptr){
            child_class->parent = object_node;
        }
        bool no_parent = strcmp(child_class->parent_name, No_class->get_string()) == 0;
        if (!parent_defined && !no_parent) {
            fprintf(stderr, "class %s inherits undefined class %s\n",
                    child_class->class_name, child_class->parent_name);
            print_halt();
            semant_errors = 1;
            exit(1);
        }
    }
}
void ClassTable::check_cycle(ClassNode *root, std::vector<ClassNode *> &visited) {
    ClassNode *cycle_root = nullptr;
    for (ClassNode *node : visited) {
        if (root->is_parent(node)) {
            cycle_root = node;
            break;
        }
    }
    if (cycle_root != nullptr) {
        auto start = std::find(visited.begin(), visited.end(), cycle_root);
        fprintf(stderr, "Cycles deteced in class hierarchy:\n");
        for (auto it = start; it < visited.end(); it++)
            fprintf(stderr, "%s->", (*it)->class_name);
        fprintf(stderr, "%s->", root->class_name);
        fprintf(stderr, "%s\n", cycle_root->class_name);
        print_halt();
        semant_errors = 1;
        exit(1);
    }
    visited.push_back(root);
    for (auto child : root->children) {
        check_cycle(child, visited);
    }
    visited.pop_back();
}

void ClassTable::check_scope_and_type() {
    SymbolTableP dummy(new SymbolTable());
    for (int i = classes->first(); classes->more(i); i = classes->next(i)) {
        static_cast<class__class *>(classes->nth(i))->check_scope_and_type(dummy, this);
    }
}

void ClassTable::free_tree() {
    for (ClassNode *node : class_nodes)
        delete node;
    object_node = nullptr;
    class_nodes.clear();
}
void ClassTable::install_basic_classes() {
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

    //
    // The Int class has no methods and only a single attribute, the
    // "val" for the integer.
    //
    Class_ Int_class =
        class_(Int,
               Object,
               single_Features(attr(val, prim_slot, no_expr())),
               filename);

    //
    // Bool also has only the "val" slot.
    //
    Class_ Bool_class =
        class_(Bool, Object, single_Features(attr(val, prim_slot, no_expr())), filename);

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
    classes = append_Classes(classes, single_Classes(Object_class));
    classes = append_Classes(classes, single_Classes(IO_class));
    classes = append_Classes(classes, single_Classes(Int_class));
    classes = append_Classes(classes, single_Classes(Bool_class));
    classes = append_Classes(classes, single_Classes(Str_class));
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

ostream &ClassTable::semant_error(Class_ c) {
    return semant_error(c->get_filename(), c);
}

ostream &ClassTable::semant_error(Symbol filename, tree_node *t) {
    error_stream << filename << ":" << t->get_line_number() << ": ";
    return semant_error();
}

ostream &ClassTable::semant_error() {
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
    ClassTable *classtable = new ClassTable(classes);
    ;
    /* some semantic analysis code may go here */

    /*Note the global symbol table has already been built
      when classtable is created
    */
    if (classtable->errors()) {
        cerr << "Compilation halted due to static semantic errors." << endl;
        exit(1);
    }
}
