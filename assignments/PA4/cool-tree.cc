//////////////////////////////////////////////////////////
//
// file: cool-tree.cc
//
// This file defines the functions of each class
//
//////////////////////////////////////////////////////////

#include "cool-tree.h"

#include "cool-tree.handcode.h"
#include "tree.h"
static Symbol SELF_TYPE = idtable.add_string("SELF_TYPE");
static Symbol Int = idtable.add_string("Int");
static Symbol String = idtable.add_string("String");
static Symbol Bool = idtable.add_string("Bool");
static Symbol No_type = idtable.add_string("_no_type");

// constructors' functions
Program program_class::copy_Program() {
    return new program_class(classes->copy_list());
}

void program_class::dump(ostream& stream, int n) {
    stream << pad(n) << "program\n";
    classes->dump(stream, n + 2);
}

Class_ class__class::copy_Class_() {
    return new class__class(copy_Symbol(name), copy_Symbol(parent), features->copy_list(), copy_Symbol(filename));
}

void class__class::dump(ostream& stream, int n) {
    stream << pad(n) << "class_\n";
    dump_Symbol(stream, n + 2, name);
    dump_Symbol(stream, n + 2, parent);
    features->dump(stream, n + 2);
    dump_Symbol(stream, n + 2, filename);
}

Feature method_class::copy_Feature() {
    return new method_class(copy_Symbol(name), formals->copy_list(), copy_Symbol(return_type), expr->copy_Expression());
}

void method_class::dump(ostream& stream, int n) {
    stream << pad(n) << "method\n";
    dump_Symbol(stream, n + 2, name);
    formals->dump(stream, n + 2);
    dump_Symbol(stream, n + 2, return_type);
    expr->dump(stream, n + 2);
}

Feature attr_class::copy_Feature() {
    return new attr_class(copy_Symbol(name), copy_Symbol(type_decl), init->copy_Expression());
}

void attr_class::dump(ostream& stream, int n) {
    stream << pad(n) << "attr\n";
    dump_Symbol(stream, n + 2, name);
    dump_Symbol(stream, n + 2, type_decl);
    init->dump(stream, n + 2);
}

Formal formal_class::copy_Formal() {
    return new formal_class(copy_Symbol(name), copy_Symbol(type_decl));
}

void formal_class::dump(ostream& stream, int n) {
    stream << pad(n) << "formal\n";
    dump_Symbol(stream, n + 2, name);
    dump_Symbol(stream, n + 2, type_decl);
}

Case branch_class::copy_Case() {
    return new branch_class(copy_Symbol(name), copy_Symbol(type_decl), expr->copy_Expression());
}

void branch_class::dump(ostream& stream, int n) {
    stream << pad(n) << "branch\n";
    dump_Symbol(stream, n + 2, name);
    dump_Symbol(stream, n + 2, type_decl);
    expr->dump(stream, n + 2);
}

Expression assign_class::copy_Expression() {
    return new assign_class(copy_Symbol(name), expr->copy_Expression());
}

void assign_class::dump(ostream& stream, int n) {
    stream << pad(n) << "assign\n";
    dump_Symbol(stream, n + 2, name);
    expr->dump(stream, n + 2);
}

Expression static_dispatch_class::copy_Expression() {
    return new static_dispatch_class(expr->copy_Expression(), copy_Symbol(type_name), copy_Symbol(name), actual->copy_list());
}

void static_dispatch_class::dump(ostream& stream, int n) {
    stream << pad(n) << "static_dispatch\n";
    expr->dump(stream, n + 2);
    dump_Symbol(stream, n + 2, type_name);
    dump_Symbol(stream, n + 2, name);
    actual->dump(stream, n + 2);
}

Expression dispatch_class::copy_Expression() {
    return new dispatch_class(expr->copy_Expression(), copy_Symbol(name), actual->copy_list());
}

void dispatch_class::dump(ostream& stream, int n) {
    stream << pad(n) << "dispatch\n";
    expr->dump(stream, n + 2);
    dump_Symbol(stream, n + 2, name);
    actual->dump(stream, n + 2);
}

Expression cond_class::copy_Expression() {
    return new cond_class(pred->copy_Expression(), then_exp->copy_Expression(), else_exp->copy_Expression());
}

void cond_class::dump(ostream& stream, int n) {
    stream << pad(n) << "cond\n";
    pred->dump(stream, n + 2);
    then_exp->dump(stream, n + 2);
    else_exp->dump(stream, n + 2);
}

Expression loop_class::copy_Expression() {
    return new loop_class(pred->copy_Expression(), body->copy_Expression());
}

void loop_class::dump(ostream& stream, int n) {
    stream << pad(n) << "loop\n";
    pred->dump(stream, n + 2);
    body->dump(stream, n + 2);
}

Expression typcase_class::copy_Expression() {
    return new typcase_class(expr->copy_Expression(), cases->copy_list());
}

void typcase_class::dump(ostream& stream, int n) {
    stream << pad(n) << "typcase\n";
    expr->dump(stream, n + 2);
    cases->dump(stream, n + 2);
}

Expression block_class::copy_Expression() {
    return new block_class(body->copy_list());
}

void block_class::dump(ostream& stream, int n) {
    stream << pad(n) << "block\n";
    body->dump(stream, n + 2);
}

Expression let_class::copy_Expression() {
    return new let_class(copy_Symbol(identifier), copy_Symbol(type_decl), init->copy_Expression(), body->copy_Expression());
}

void let_class::dump(ostream& stream, int n) {
    stream << pad(n) << "let\n";
    dump_Symbol(stream, n + 2, identifier);
    dump_Symbol(stream, n + 2, type_decl);
    init->dump(stream, n + 2);
    body->dump(stream, n + 2);
}

Expression plus_class::copy_Expression() {
    return new plus_class(e1->copy_Expression(), e2->copy_Expression());
}

void plus_class::dump(ostream& stream, int n) {
    stream << pad(n) << "plus\n";
    e1->dump(stream, n + 2);
    e2->dump(stream, n + 2);
}

Expression sub_class::copy_Expression() {
    return new sub_class(e1->copy_Expression(), e2->copy_Expression());
}

void sub_class::dump(ostream& stream, int n) {
    stream << pad(n) << "sub\n";
    e1->dump(stream, n + 2);
    e2->dump(stream, n + 2);
}

Expression mul_class::copy_Expression() {
    return new mul_class(e1->copy_Expression(), e2->copy_Expression());
}

void mul_class::dump(ostream& stream, int n) {
    stream << pad(n) << "mul\n";
    e1->dump(stream, n + 2);
    e2->dump(stream, n + 2);
}

Expression divide_class::copy_Expression() {
    return new divide_class(e1->copy_Expression(), e2->copy_Expression());
}

void divide_class::dump(ostream& stream, int n) {
    stream << pad(n) << "divide\n";
    e1->dump(stream, n + 2);
    e2->dump(stream, n + 2);
}

Expression neg_class::copy_Expression() {
    return new neg_class(e1->copy_Expression());
}

void neg_class::dump(ostream& stream, int n) {
    stream << pad(n) << "neg\n";
    e1->dump(stream, n + 2);
}

Expression lt_class::copy_Expression() {
    return new lt_class(e1->copy_Expression(), e2->copy_Expression());
}

void lt_class::dump(ostream& stream, int n) {
    stream << pad(n) << "lt\n";
    e1->dump(stream, n + 2);
    e2->dump(stream, n + 2);
}

Expression eq_class::copy_Expression() {
    return new eq_class(e1->copy_Expression(), e2->copy_Expression());
}

void eq_class::dump(ostream& stream, int n) {
    stream << pad(n) << "eq\n";
    e1->dump(stream, n + 2);
    e2->dump(stream, n + 2);
}

Expression leq_class::copy_Expression() {
    return new leq_class(e1->copy_Expression(), e2->copy_Expression());
}

void leq_class::dump(ostream& stream, int n) {
    stream << pad(n) << "leq\n";
    e1->dump(stream, n + 2);
    e2->dump(stream, n + 2);
}

Expression comp_class::copy_Expression() {
    return new comp_class(e1->copy_Expression());
}

void comp_class::dump(ostream& stream, int n) {
    stream << pad(n) << "comp\n";
    e1->dump(stream, n + 2);
}

Expression int_const_class::copy_Expression() {
    return new int_const_class(copy_Symbol(token));
}

void int_const_class::dump(ostream& stream, int n) {
    stream << pad(n) << "int_const\n";
    dump_Symbol(stream, n + 2, token);
}

Expression bool_const_class::copy_Expression() {
    return new bool_const_class(copy_Boolean(val));
}

void bool_const_class::dump(ostream& stream, int n) {
    stream << pad(n) << "bool_const\n";
    dump_Boolean(stream, n + 2, val);
}

Expression string_const_class::copy_Expression() {
    return new string_const_class(copy_Symbol(token));
}

void string_const_class::dump(ostream& stream, int n) {
    stream << pad(n) << "string_const\n";
    dump_Symbol(stream, n + 2, token);
}

Expression new__class::copy_Expression() {
    return new new__class(copy_Symbol(type_name));
}

void new__class::dump(ostream& stream, int n) {
    stream << pad(n) << "new_\n";
    dump_Symbol(stream, n + 2, type_name);
}

Expression isvoid_class::copy_Expression() {
    return new isvoid_class(e1->copy_Expression());
}

void isvoid_class::dump(ostream& stream, int n) {
    stream << pad(n) << "isvoid\n";
    e1->dump(stream, n + 2);
}

Expression no_expr_class::copy_Expression() {
    return new no_expr_class();
}

void no_expr_class::dump(ostream& stream, int n) {
    stream << pad(n) << "no_expr\n";
}

Expression object_class::copy_Expression() {
    return new object_class(copy_Symbol(name));
}

void object_class::dump(ostream& stream, int n) {
    stream << pad(n) << "object\n";
    dump_Symbol(stream, n + 2, name);
}

// interfaces used by Bison
Classes nil_Classes() {
    return new nil_node<Class_>();
}

Classes single_Classes(Class_ e) {
    return new single_list_node<Class_>(e);
}

Classes append_Classes(Classes p1, Classes p2) {
    return new append_node<Class_>(p1, p2);
}

Features nil_Features() {
    return new nil_node<Feature>();
}

Features single_Features(Feature e) {
    return new single_list_node<Feature>(e);
}

Features append_Features(Features p1, Features p2) {
    return new append_node<Feature>(p1, p2);
}

Formals nil_Formals() {
    return new nil_node<Formal>();
}

Formals single_Formals(Formal e) {
    return new single_list_node<Formal>(e);
}

Formals append_Formals(Formals p1, Formals p2) {
    return new append_node<Formal>(p1, p2);
}

Expressions nil_Expressions() {
    return new nil_node<Expression>();
}

Expressions single_Expressions(Expression e) {
    return new single_list_node<Expression>(e);
}

Expressions append_Expressions(Expressions p1, Expressions p2) {
    return new append_node<Expression>(p1, p2);
}

Cases nil_Cases() {
    return new nil_node<Case>();
}

Cases single_Cases(Case e) {
    return new single_list_node<Case>(e);
}

Cases append_Cases(Cases p1, Cases p2) {
    return new append_node<Case>(p1, p2);
}

Program program(Classes classes) {
    return new program_class(classes);
}

Class_ class_(Symbol name, Symbol parent, Features features, Symbol filename) {
    return new class__class(name, parent, features, filename);
}

Feature method(Symbol name, Formals formals, Symbol return_type, Expression expr) {
    return new method_class(name, formals, return_type, expr);
}

Feature attr(Symbol name, Symbol type_decl, Expression init) {
    return new attr_class(name, type_decl, init);
}

Formal formal(Symbol name, Symbol type_decl) {
    return new formal_class(name, type_decl);
}

Case branch(Symbol name, Symbol type_decl, Expression expr) {
    return new branch_class(name, type_decl, expr);
}

Expression assign(Symbol name, Expression expr) {
    return new assign_class(name, expr);
}

Expression static_dispatch(Expression expr, Symbol type_name, Symbol name, Expressions actual) {
    return new static_dispatch_class(expr, type_name, name, actual);
}

Expression dispatch(Expression expr, Symbol name, Expressions actual) {
    return new dispatch_class(expr, name, actual);
}

Expression cond(Expression pred, Expression then_exp, Expression else_exp) {
    return new cond_class(pred, then_exp, else_exp);
}

Expression loop(Expression pred, Expression body) {
    return new loop_class(pred, body);
}

Expression typcase(Expression expr, Cases cases) {
    return new typcase_class(expr, cases);
}

Expression block(Expressions body) {
    return new block_class(body);
}

Expression let(Symbol identifier, Symbol type_decl, Expression init, Expression body) {
    return new let_class(identifier, type_decl, init, body);
}

Expression plus(Expression e1, Expression e2) {
    return new plus_class(e1, e2);
}

Expression sub(Expression e1, Expression e2) {
    return new sub_class(e1, e2);
}

Expression mul(Expression e1, Expression e2) {
    return new mul_class(e1, e2);
}

Expression divide(Expression e1, Expression e2) {
    return new divide_class(e1, e2);
}

Expression neg(Expression e1) {
    return new neg_class(e1);
}

Expression lt(Expression e1, Expression e2) {
    return new lt_class(e1, e2);
}

Expression eq(Expression e1, Expression e2) {
    return new eq_class(e1, e2);
}

Expression leq(Expression e1, Expression e2) {
    return new leq_class(e1, e2);
}

Expression comp(Expression e1) {
    return new comp_class(e1);
}

Expression int_const(Symbol token) {
    return new int_const_class(token);
}

Expression bool_const(Boolean val) {
    return new bool_const_class(val);
}

Expression string_const(Symbol token) {
    return new string_const_class(token);
}

Expression new_(Symbol type_name) {
    return new new__class(type_name);
}

Expression isvoid(Expression e1) {
    return new isvoid_class(e1);
}

Expression no_expr() {
    return new no_expr_class();
}

Expression object(Symbol name) {
    return new object_class(name);
}

bool is_subclass(Symbol subclass_name, Symbol superclass_name) {
    ClassNodeP subclass_node = class_table[subclass_name];
    ClassNodeP curr_node = subclass_node;
    while (curr_node != nullptr && curr_node->value->name != superclass_name) {
        curr_node = curr_node->parent;
    }
    return curr_node != nullptr;
}

int arg_match(Expressions actual, Formals formals, Expression curr_exp, char* filename, Symbol self_type) {
    int errors = 0;
    if (actual->len() != formals->len()) {
        fprintf(stderr, "%s:%d: static dispatch has incorrect number of arguments: need %d, get %d\n", filename, curr_exp->get_line_number(), formals->len(), actual->len());
        errors++;
        return errors;
    }
    int i;
    int j;
    Expression expr;
    formal_class* formal;
    int num_arg = 0;
    for (i = actual->first(), j = formals->first(); actual->more(i); i = actual->next(i), j = formals->next(j)) {
        num_arg++;
        expr = actual->nth(i);
        formal = (formal_class*)formals->nth(j);
        Symbol formal_type = formal->type_decl;
        if (formal_type == SELF_TYPE)
            formal_type = self_type;
        // if (expr->type != formal_type) {
        if (!is_subclass(expr->actual_type, formal_type)) {
            fprintf(stderr, "%s:%d: %dth argument of static dispatch has the wrong type. Expect %s, get %s\n", filename, curr_exp->get_line_number(), num_arg, formal_type->get_string(), expr->type->get_string());
            errors++;
        }
    }
    return errors;
}

int int_op_check(Expression e1, Expression e2, SymbolTableP symbol_table, int line_num, char* filename) {
    int errors = 0;
    errors += e1->check_and_annotate(symbol_table, filename);
    if (e1->type != idtable.add_string("Int")) {
        fprintf(stderr, "%s:%d: expression before requires type Int, gets %s\n", filename, line_num, e1->type->get_string());
        errors++;
    }
    errors += e2->check_and_annotate(symbol_table, filename);
    if (e2->type != idtable.add_string("Int")) {
        fprintf(stderr, "%s:%d: expression after requires type Int, gets %s\n", filename, line_num, e2->type->get_string());
        errors++;
    }
    return errors;
}

int bool_op_check(Expression e1, Expression e2, SymbolTableP symbol_table, int line_num, char* filename) {
    int errors = 0;
    errors += e1->check_and_annotate(symbol_table, filename);
    if (e1->type != idtable.add_string("Bool")) {
        fprintf(stderr, "%s:%d: expression before requires type Bool, gets %s\n", filename, line_num, e1->type->get_string());
        errors++;
    }
    errors += e2->check_and_annotate(symbol_table, filename);
    if (e2->type != idtable.add_string("Bool")) {
        fprintf(stderr, "%s:%d: expression after requires type Bool, gets %s\n", filename, line_num, e2->type->get_string());
        errors++;
    }
    return errors;
}

Symbol union_type(Symbol a, Symbol b) {
    ClassNodeP node_a = class_table[a];
    ClassNodeP node_b = class_table[b];
    std::vector<ClassNodeP> path_a = get_path(node_a);
    std::vector<ClassNodeP> path_b = get_path(node_b);
    for (ClassNodeP n_a : path_a) {
        for (ClassNodeP n_b : path_b) {
            if (n_a == n_b)
                return n_a->value->name;
        }
    }
    return nullptr;
}

std::vector<ClassNodeP> get_path(ClassNodeP node) {
    std::vector<ClassNodeP> result;
    ClassNodeP curr = node;
    while (curr != nullptr) {
        result.push_back(curr);
        curr = curr->parent;
    }
    return result;
}

int class__class::check_and_annotate(SymbolTableP symbol_table, char* filename) {
    int errors = 0;
    symbol_table->objects.clear();
    symbol_table->add_object(idtable.add_string("self"), Info(SELF_TYPE));
    for (int i = features->first(); features->more(i); i = features->next(i)) {
        errors += features->nth(i)->check_and_annotate(symbol_table, filename);
    }
    return errors;
}

int method_class::check_and_annotate(SymbolTableP symbol_table, char* filename) {
    //create a new table for method scope,pointing to the parent table
    int errors = 0;
    symbol_table = new SymbolTable(symbol_table);
    for (int i = formals->first(); formals->more(i); i = formals->next(i)) {
        formal_class* formal = (formal_class*)formals->nth(i);
        symbol_table->add_object(formal->name, Info(formal->type_decl));
    }
    errors += expr->check_and_annotate(symbol_table, filename);
    Symbol actual_return_type = return_type;
    if(actual_return_type == SELF_TYPE)
        actual_return_type = symbol_table->get_self_type();
    if(!is_subclass(expr->actual_type, actual_return_type)){
        fprintf(stderr, "%s:%d:inferred return type %s doesn't conform to expected return type %s\n",filename,get_line_number(),expr->actual_type->get_string(),actual_return_type->get_string());
        errors++;
    }
    delete symbol_table;
    return errors;
}

int attr_class::check_and_annotate(SymbolTableP symbol_table, char* filename) {
    int errors = 0;
    // symbol_table->objects.erase(name);
    errors += init->check_and_annotate(symbol_table, filename);
    symbol_table->objects[name] = Info(type_decl);
    return errors;
}

int formal_class::check_and_annotate(SymbolTableP symbol_table, char* filename) {
    return 0;
}

int branch_class::check_and_annotate(SymbolTableP symbol_table, char* filename) {
    int errors = 0;
    symbol_table = new SymbolTable(symbol_table);
    Symbol var_type  = type_decl;
    if(var_type == SELF_TYPE){
        fprintf(stderr, "%s:%d: SELF_TYPE used in branch\n",filename,get_line_number());
        var_type = idtable.add_string("Object");
        errors++;
    }
    symbol_table->add_object(name, Info(var_type));
    errors += expr->check_and_annotate(symbol_table, filename);
    delete symbol_table;
    return errors;
}

int assign_class::check_and_annotate(SymbolTableP symbol_table, char* filename) {
    int errors = 0;
    Info&& object_info = symbol_table->look_up_object(name);
    type = actual_type = idtable.add_string("Object");

    if(name == idtable.add_string("self")){
        fprintf(stderr, "%s:%d: assign to self is prohibited\n",filename,get_line_number());
        errors++;
        return errors;
    }
    if (object_info.type == nullptr) {
        fprintf(stderr, "%s:%d: object %s doesn't exist\n", filename, get_line_number(), name->get_string());
        errors++;
        return errors;
    }
    errors += expr->check_and_annotate(symbol_table, filename);
    // Assigning type to the expression
    Symbol object_type = object_info.type;
    if (object_type == SELF_TYPE)
        object_type = symbol_table->get_self_type();
    if (!is_subclass(expr->actual_type, object_type)) {
        fprintf(stderr, "%s:%d: object %s has type %s while the assigned expression has type %s\n", filename, get_line_number(), name->get_string(), object_type->get_string(), expr->actual_type->get_string());
        errors++;
        return errors;
    }
    type = expr->type;
    actual_type = expr->actual_type;
    return errors;
}

int static_dispatch_class::check_and_annotate(SymbolTableP symbol_table, char* filename) {
    int errors = 0;
    errors += expr->check_and_annotate(symbol_table, filename);
    Symbol dispatch_type = type_name;
    type = actual_type = idtable.add_string("Object");
    if (dispatch_type == SELF_TYPE)
        dispatch_type = symbol_table->get_self_type();
    if (!is_subclass(expr->type, dispatch_type)) {
        fprintf(stderr, "%s:%d: expression has type %s which is not a subtype of dispatch type %s\n", filename, get_line_number(), expr->type->get_string(), dispatch_type->get_string());
        errors++;
        return errors;
    }
    if (class_level_tables[type_name]->look_up_method(name).type == nullptr) {
        fprintf(stderr, "%s:%d: method %s doesn't exist\n", filename, get_line_number(), name->get_string());
        errors++;
        return errors;
    }
    Info&& method_info = class_level_tables[type_name]->look_up_method(name);
    Formals formals = method_info.formals;
    for (int i = actual->first(); actual->more(i); i = actual->next(i)) {
        Expression e = actual->nth(i);
        errors += e->check_and_annotate(symbol_table, filename);
    }
    errors += arg_match(actual, formals, this, filename, symbol_table->get_self_type());
    // Assigning type to the expression
    type = actual_type = method_info.type;
    if (actual_type == SELF_TYPE)
        type = actual_type =expr->type;
    return errors;
}

int dispatch_class::check_and_annotate(SymbolTableP symbol_table, char* filename) {
    int errors = 0;
    errors += expr->check_and_annotate(symbol_table, filename);
    type = actual_type = idtable.add_string("Object");
    SymbolTableP method_table = class_level_tables[expr->actual_type];
    if (method_table->look_up_method(name).type == nullptr) {
        fprintf(stderr, "%s:%d: method %s doesn't exist\n", filename, get_line_number(), name->get_string());
        errors++;
        return errors;
    }

    Info&& method_info = method_table->look_up_method(name);
    Formals formals = method_info.formals;
    for (int i = actual->first(); actual->more(i); i = actual->next(i)) {
        Expression e = actual->nth(i);
        errors += e->check_and_annotate(symbol_table, filename);
    }
    errors += arg_match(actual, formals, this, filename, symbol_table->get_self_type());
    actual_type = type = method_info.type;
    if (actual_type == SELF_TYPE){
        type = expr->type;
        actual_type=expr->actual_type;
    }
    return errors;
}

int cond_class::check_and_annotate(SymbolTableP symbol_table, char* filename) {
    int errors = 0;
    errors += pred->check_and_annotate(symbol_table, filename);
    if (pred->type != idtable.add_string("Bool")) {
        fprintf(stderr, "%s:%d: predicate requires Bool, gets %s\n", filename, get_line_number(), pred->type->get_string());
        errors++;
    }
    errors += then_exp->check_and_annotate(symbol_table, filename);
    errors += else_exp->check_and_annotate(symbol_table, filename);
    actual_type = type = union_type(then_exp->actual_type, else_exp->actual_type);
    return errors;
}

int loop_class::check_and_annotate(SymbolTableP symbol_table, char* filename) {
    int errors = 0;
    errors += pred->check_and_annotate(symbol_table, filename);
    if (pred->type != idtable.add_string("Bool")) {
        fprintf(stderr, "%s:%d: predicate requires Bool, gets %s\n", filename, get_line_number(), pred->type->get_string());
        errors++;
    }

    errors += body->check_and_annotate(symbol_table, filename);
    actual_type = type = idtable.add_string("Object");
    return errors;
}

int typcase_class::check_and_annotate(SymbolTableP symbol_table, char* filename) {
    int errors = 0;
    std::unordered_set<Symbol> visited; 
    errors += expr->check_and_annotate(symbol_table, filename);
    int i = cases->first();
    branch_class* first_case = (branch_class*)cases->nth(i);
    first_case->check_and_annotate(symbol_table, filename);
    type = first_case->expr->actual_type;
    visited.insert(first_case->type_decl);
    for (i = cases->next(i); cases->more(i); i = cases->next(i)) {
        branch_class* one_case = (branch_class*)cases->nth(i);
        if(visited.find(one_case->type_decl) != visited.end()){
            fprintf(stderr, "%s:%d: redefinition of branch type %s\n",filename,get_line_number(),one_case->type_decl->get_string());
            errors++;
        }
        visited.insert(one_case->type_decl);
        errors += one_case->check_and_annotate(symbol_table, filename);
        type = union_type(type, one_case->expr->actual_type);
    }
    actual_type = type;
    return errors;
}

int block_class::check_and_annotate(SymbolTableP symbol_table, char* filename) {
    int errors = 0;
    for (int i = body->first(); body->more(i); i = body->next(i)) {
        Expression expr = body->nth(i);
        errors += expr->check_and_annotate(symbol_table, filename);
        type = expr->type;
        actual_type  = expr->actual_type;
    }
    return errors;
}

int let_class::check_and_annotate(SymbolTableP symbol_table, char* filename) {
    int errors = 0;
    errors += init->check_and_annotate(symbol_table, filename);
    Symbol var_type = type_decl;
    if (var_type == SELF_TYPE)
        var_type = symbol_table->get_self_type();
    if (init->type != No_type && !is_subclass(init->actual_type, var_type)) {
        fprintf(stderr, "%s:%d: object %s requires type %s while is initialized to type %s\n", filename, get_line_number(), identifier->get_string(), var_type->get_string(), init->actual_type->get_string());
        errors++;
    }
    symbol_table = new SymbolTable(symbol_table);
    if(identifier == idtable.add_string("self")){
        fprintf(stderr, "%s:%d: self is not a valid identifier for let\n",filename,get_line_number());
        errors++;
    }else{
        symbol_table->add_object(identifier, Info(type_decl));
    }
    errors += body->check_and_annotate(symbol_table, filename);
    type = body->type;
    actual_type = body->actual_type;
    return errors;
}

int plus_class::check_and_annotate(SymbolTableP symbol_table, char* filename) {
    actual_type = type = idtable.add_string("Int");
    return int_op_check(e1, e2, symbol_table, get_line_number(), filename);
}

int sub_class::check_and_annotate(SymbolTableP symbol_table, char* filename) {
    actual_type = type = idtable.add_string("Int");
    return int_op_check(e1, e2, symbol_table, get_line_number(), filename);
}

int mul_class::check_and_annotate(SymbolTableP symbol_table, char* filename) {
    actual_type =type = idtable.add_string("Int");
    return int_op_check(e1, e2, symbol_table, get_line_number(), filename);
}

int divide_class::check_and_annotate(SymbolTableP symbol_table, char* filename) {
    actual_type =type = idtable.add_string("Int");
    return int_op_check(e1, e2, symbol_table, get_line_number(), filename);
}

int neg_class::check_and_annotate(SymbolTableP symbol_table, char* filename) {
    int errors = 0;
    errors += e1->check_and_annotate(symbol_table, filename);
    if (e1->type != idtable.add_string("Int")) {
        fprintf(stderr, "%s:%d: expression requires type Int, gets %s\n", filename, get_line_number(), e1->type->get_string());
        errors++;
    }
    actual_type =type = idtable.add_string("Int");
    return errors;
}

int lt_class::check_and_annotate(SymbolTableP symbol_table, char* filename) {
    actual_type =type = idtable.add_string("Bool");
    return int_op_check(e1, e2, symbol_table, get_line_number(), filename);
}

int eq_class::check_and_annotate(SymbolTableP symbol_table, char* filename) {
    int errors = 0;
    errors += e1->check_and_annotate(symbol_table,filename);
    errors += e2->check_and_annotate(symbol_table,filename);
    Symbol e1_type = e1->get_type();
    Symbol e2_type = e2->get_type();
    std::unordered_set<Symbol> basic_types{Int, String, Bool};
    if(basic_types.find(e1_type) != basic_types.end() || basic_types.find(e2_type) != basic_types.end()){
       if(e1_type != e2_type){
           fprintf(stderr, "%s:%d: e1 has type %s while e2 has type %s\n",filename,get_line_number(),e1_type->get_string(),e2_type->get_string());
           errors++;
       } 
    }
    actual_type =type = idtable.add_string("Bool");
    return errors ;
}

int leq_class::check_and_annotate(SymbolTableP symbol_table, char* filename) {
    actual_type =type = idtable.add_string("Bool");
    return int_op_check(e1, e2, symbol_table, get_line_number(), filename);
}

int comp_class::check_and_annotate(SymbolTableP symbol_table, char* filename) {
    int errors = 0;
    errors += e1->check_and_annotate(symbol_table, filename);
    if (e1->type != idtable.add_string("Bool")) {
        fprintf(stderr, "%s:%d: expression requires type Bool get %s\n", filename, get_line_number(), e1->type->get_string());
        errors++;
    }
    actual_type =type = idtable.add_string("Bool");
    return errors;
}

int int_const_class::check_and_annotate(SymbolTableP symbol_table, char* filename) {
    actual_type =type = idtable.add_string("Int");
    return 0;
}

int bool_const_class::check_and_annotate(SymbolTableP symbol_table, char* filename) {
    actual_type =type = idtable.add_string("Bool");
    return 0;
}

int string_const_class::check_and_annotate(SymbolTableP symbol_table, char* filename) {
    actual_type =type = idtable.add_string("String");
    return 0;
}

int new__class::check_and_annotate(SymbolTableP symbol_table, char* filename) {
    actual_type = type = type_name;
    if(actual_type == SELF_TYPE )
        actual_type = symbol_table->get_self_type();
    return 0;
}

int isvoid_class::check_and_annotate(SymbolTableP symbol_table, char* filename) {
    int errors = e1->check_and_annotate(symbol_table, filename);
    actual_type =type = idtable.add_string("Bool");
    return 0;
}

int no_expr_class::check_and_annotate(SymbolTableP symbol_table, char* filename) {
    actual_type =type = idtable.add_string("_no_type");
    return 0;
}

int object_class::check_and_annotate(SymbolTableP symbol_table, char* filename) {
    int errors = 0;
    type = symbol_table->look_up_object(name).type;
    if (type == nullptr) {
        fprintf(stderr, "%s:%d: Object %s doesn't exist\n", filename, get_line_number(), name->get_string());
        errors++;
        type = idtable.add_string("Object");
    }
    actual_type = type;
    if (actual_type == SELF_TYPE) {
        actual_type = symbol_table->get_self_type();
    }
    return errors;
}
