//////////////////////////////////////////////////////////
//
// file: cool-tree.cc
//
// This file defines the functions of each class
//
//////////////////////////////////////////////////////////

#include "cool-tree.h"

#include <stdexcept>
#include <string>

#include "cool-tree.handcode.h"
#include "semant.h"
#include "tree.h"

// constructors' functions
Program program_class::copy_Program() {
    return new program_class(classes->copy_list());
}

void program_class::dump(ostream &stream, int n) {
    stream << pad(n) << "program\n";
    classes->dump(stream, n + 2);
}

Class_ class__class::copy_Class_() {
    return new class__class(copy_Symbol(name), copy_Symbol(parent), features->copy_list(), copy_Symbol(filename));
}

void class__class::dump(ostream &stream, int n) {
    stream << pad(n) << "class_\n";
    dump_Symbol(stream, n + 2, name);
    dump_Symbol(stream, n + 2, parent);
    features->dump(stream, n + 2);
    dump_Symbol(stream, n + 2, filename);
}

Feature method_class::copy_Feature() {
    return new method_class(copy_Symbol(name), formals->copy_list(), copy_Symbol(return_type), expr->copy_Expression());
}

void method_class::dump(ostream &stream, int n) {
    stream << pad(n) << "method\n";
    dump_Symbol(stream, n + 2, name);
    formals->dump(stream, n + 2);
    dump_Symbol(stream, n + 2, return_type);
    expr->dump(stream, n + 2);
}

Feature attr_class::copy_Feature() {
    return new attr_class(copy_Symbol(name), copy_Symbol(type_decl), init->copy_Expression());
}

void attr_class::dump(ostream &stream, int n) {
    stream << pad(n) << "attr\n";
    dump_Symbol(stream, n + 2, name);
    dump_Symbol(stream, n + 2, type_decl);
    init->dump(stream, n + 2);
}

Formal formal_class::copy_Formal() {
    return new formal_class(copy_Symbol(name), copy_Symbol(type_decl));
}

void formal_class::dump(ostream &stream, int n) {
    stream << pad(n) << "formal\n";
    dump_Symbol(stream, n + 2, name);
    dump_Symbol(stream, n + 2, type_decl);
}

Case branch_class::copy_Case() {
    return new branch_class(copy_Symbol(name), copy_Symbol(type_decl), expr->copy_Expression());
}

void branch_class::dump(ostream &stream, int n) {
    stream << pad(n) << "branch\n";
    dump_Symbol(stream, n + 2, name);
    dump_Symbol(stream, n + 2, type_decl);
    expr->dump(stream, n + 2);
}

Expression assign_class::copy_Expression() {
    return new assign_class(copy_Symbol(name), expr->copy_Expression());
}

void assign_class::dump(ostream &stream, int n) {
    stream << pad(n) << "assign\n";
    dump_Symbol(stream, n + 2, name);
    expr->dump(stream, n + 2);
}

Expression static_dispatch_class::copy_Expression() {
    return new static_dispatch_class(expr->copy_Expression(), copy_Symbol(type_name), copy_Symbol(name), actual->copy_list());
}

void static_dispatch_class::dump(ostream &stream, int n) {
    stream << pad(n) << "static_dispatch\n";
    expr->dump(stream, n + 2);
    dump_Symbol(stream, n + 2, type_name);
    dump_Symbol(stream, n + 2, name);
    actual->dump(stream, n + 2);
}

Expression dispatch_class::copy_Expression() {
    return new dispatch_class(expr->copy_Expression(), copy_Symbol(name), actual->copy_list());
}

void dispatch_class::dump(ostream &stream, int n) {
    stream << pad(n) << "dispatch\n";
    expr->dump(stream, n + 2);
    dump_Symbol(stream, n + 2, name);
    actual->dump(stream, n + 2);
}

Expression cond_class::copy_Expression() {
    return new cond_class(pred->copy_Expression(), then_exp->copy_Expression(), else_exp->copy_Expression());
}

void cond_class::dump(ostream &stream, int n) {
    stream << pad(n) << "cond\n";
    pred->dump(stream, n + 2);
    then_exp->dump(stream, n + 2);
    else_exp->dump(stream, n + 2);
}

Expression loop_class::copy_Expression() {
    return new loop_class(pred->copy_Expression(), body->copy_Expression());
}

void loop_class::dump(ostream &stream, int n) {
    stream << pad(n) << "loop\n";
    pred->dump(stream, n + 2);
    body->dump(stream, n + 2);
}

Expression typcase_class::copy_Expression() {
    return new typcase_class(expr->copy_Expression(), cases->copy_list());
}

void typcase_class::dump(ostream &stream, int n) {
    stream << pad(n) << "typcase\n";
    expr->dump(stream, n + 2);
    cases->dump(stream, n + 2);
}

Expression block_class::copy_Expression() {
    return new block_class(body->copy_list());
}

void block_class::dump(ostream &stream, int n) {
    stream << pad(n) << "block\n";
    body->dump(stream, n + 2);
}

Expression let_class::copy_Expression() {
    return new let_class(copy_Symbol(identifier), copy_Symbol(type_decl), init->copy_Expression(), body->copy_Expression());
}

void let_class::dump(ostream &stream, int n) {
    stream << pad(n) << "let\n";
    dump_Symbol(stream, n + 2, identifier);
    dump_Symbol(stream, n + 2, type_decl);
    init->dump(stream, n + 2);
    body->dump(stream, n + 2);
}

Expression plus_class::copy_Expression() {
    return new plus_class(e1->copy_Expression(), e2->copy_Expression());
}

void plus_class::dump(ostream &stream, int n) {
    stream << pad(n) << "plus\n";
    e1->dump(stream, n + 2);
    e2->dump(stream, n + 2);
}

Expression sub_class::copy_Expression() {
    return new sub_class(e1->copy_Expression(), e2->copy_Expression());
}

void sub_class::dump(ostream &stream, int n) {
    stream << pad(n) << "sub\n";
    e1->dump(stream, n + 2);
    e2->dump(stream, n + 2);
}

Expression mul_class::copy_Expression() {
    return new mul_class(e1->copy_Expression(), e2->copy_Expression());
}

void mul_class::dump(ostream &stream, int n) {
    stream << pad(n) << "mul\n";
    e1->dump(stream, n + 2);
    e2->dump(stream, n + 2);
}

Expression divide_class::copy_Expression() {
    return new divide_class(e1->copy_Expression(), e2->copy_Expression());
}

void divide_class::dump(ostream &stream, int n) {
    stream << pad(n) << "divide\n";
    e1->dump(stream, n + 2);
    e2->dump(stream, n + 2);
}

Expression neg_class::copy_Expression() {
    return new neg_class(e1->copy_Expression());
}

void neg_class::dump(ostream &stream, int n) {
    stream << pad(n) << "neg\n";
    e1->dump(stream, n + 2);
}

Expression lt_class::copy_Expression() {
    return new lt_class(e1->copy_Expression(), e2->copy_Expression());
}

void lt_class::dump(ostream &stream, int n) {
    stream << pad(n) << "lt\n";
    e1->dump(stream, n + 2);
    e2->dump(stream, n + 2);
}

Expression eq_class::copy_Expression() {
    return new eq_class(e1->copy_Expression(), e2->copy_Expression());
}

void eq_class::dump(ostream &stream, int n) {
    stream << pad(n) << "eq\n";
    e1->dump(stream, n + 2);
    e2->dump(stream, n + 2);
}

Expression leq_class::copy_Expression() {
    return new leq_class(e1->copy_Expression(), e2->copy_Expression());
}

void leq_class::dump(ostream &stream, int n) {
    stream << pad(n) << "leq\n";
    e1->dump(stream, n + 2);
    e2->dump(stream, n + 2);
}

Expression comp_class::copy_Expression() {
    return new comp_class(e1->copy_Expression());
}

void comp_class::dump(ostream &stream, int n) {
    stream << pad(n) << "comp\n";
    e1->dump(stream, n + 2);
}

Expression int_const_class::copy_Expression() {
    return new int_const_class(copy_Symbol(token));
}

void int_const_class::dump(ostream &stream, int n) {
    stream << pad(n) << "int_const\n";
    dump_Symbol(stream, n + 2, token);
}

Expression bool_const_class::copy_Expression() {
    return new bool_const_class(copy_Boolean(val));
}

void bool_const_class::dump(ostream &stream, int n) {
    stream << pad(n) << "bool_const\n";
    dump_Boolean(stream, n + 2, val);
}

Expression string_const_class::copy_Expression() {
    return new string_const_class(copy_Symbol(token));
}

void string_const_class::dump(ostream &stream, int n) {
    stream << pad(n) << "string_const\n";
    dump_Symbol(stream, n + 2, token);
}

Expression new__class::copy_Expression() {
    return new new__class(copy_Symbol(type_name));
}

void new__class::dump(ostream &stream, int n) {
    stream << pad(n) << "new_\n";
    dump_Symbol(stream, n + 2, type_name);
}

Expression isvoid_class::copy_Expression() {
    return new isvoid_class(e1->copy_Expression());
}

void isvoid_class::dump(ostream &stream, int n) {
    stream << pad(n) << "isvoid\n";
    e1->dump(stream, n + 2);
}

Expression no_expr_class::copy_Expression() {
    return new no_expr_class();
}

void no_expr_class::dump(ostream &stream, int n) {
    stream << pad(n) << "no_expr\n";
}

Expression object_class::copy_Expression() {
    return new object_class(copy_Symbol(name));
}

void object_class::dump(ostream &stream, int n) {
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

void program_class::check_scope_and_type(SymbolTableP symbol_table, ClassTableP class_table) {
    for (int i = classes->first(); classes->more(i); i = classes->next(i)) {
        class__class *class_ = static_cast<class__class *>(classes->nth(i));
        class_->check_scope_and_type(symbol_table, class_table);
    }
}

void class__class::check_scope_and_type(SymbolTableP symbol_table, ClassTableP class_table) {
    SymbolTableP new_table(new SymbolTable());
    new_table->parent = symbol_table;
    new_table->objects = SymbolTable::global_objects[name];
    new_table->methods = SymbolTable::global_methods[name];
    for (int i = features->first(); features->more(i); i = features->next(i)) {
        Feature feature = features->nth(i);
        feature->check_scope_and_type(new_table, class_table);
    }
}

void method_class::check_scope_and_type(SymbolTableP symbol_table, ClassTableP class_table) {
    SymbolTableP new_table(new SymbolTable());
    new_table->parent = symbol_table;
    SymbolData &result = symbol_table->look_up_class(return_type);
    if (result.type == not_a_symbol) {
        fprintf(stderr, "Line %d:Return type %s doesn't exist\n", get_line_number(), return_type->get_string());
        class_table->semant_error();
    }
    for (int i = formals->first(); formals->more(i); i = formals->next(i)) {
        formal_class *formal = static_cast<formal_class *>(formals->nth(i));
        SymbolData data(SymbolType::parameter_type);
        symbol_table->add_object(formal->name, data);
        /*it's OK to check validity of formals while we are building new table
        since we only check if each formal uses a valid type which are in global scope.
      */
        formal->check_scope_and_type(symbol_table, class_table);
    }
    expr->check_scope_and_type(new_table, class_table);
}

void attr_class::check_scope_and_type(SymbolTableP symbol_table, ClassTableP class_table) {
    SymbolData &result = symbol_table->look_up_class(type_decl);
    if (result.type == not_a_symbol) {
        class_table->semant_error();
        fprintf(stderr, "Line %d: class(type) %s is not defined\n", get_line_number(), type_decl->get_string());
    }
    init->check_scope_and_type(symbol_table, class_table);
}

void formal_class::check_scope_and_type(SymbolTableP symbol_table, ClassTableP class_table) {
    SymbolData &result = symbol_table->look_up_class(type_decl);
    if (result.type == not_a_symbol) {
        fprintf(stderr, "Line %d: class(type) %s is not defined\n", get_line_number(), type_decl->get_string());
        class_table->semant_error();
    }
}

void branch_class::check_scope_and_type(SymbolTableP symbol_table, ClassTableP class_table) {
    if (symbol_table->look_up_class(type_decl).type == not_a_symbol) {
        fprintf(stderr, "Line %d: class(type) %s is not defined\n", get_line_number(), type_decl->get_string());
        class_table->semant_error();
    }
    SymbolTableP new_table(new SymbolTable());
    new_table->parent = symbol_table;
    new_table->add_object(name, SymbolData(SymbolType::case_type));
    expr->check_scope_and_type(new_table, class_table);
}

/*
   TODO: the current symbol is added after check scope.
   Consequently the order to go through expression blocks
   matters.*/
void assign_class::check_scope_and_type(SymbolTableP symbol_table, ClassTableP class_table) {
    expr->check_scope_and_type(symbol_table, class_table);
    symbol_table->add_object(name, SymbolData(SymbolType::assign_type));
}

void static_dispatch_class::check_scope_and_type(SymbolTableP symbol_table, ClassTableP class_table) {
    expr->check_scope_and_type(symbol_table, class_table);
    if (symbol_table->look_up_class(type_name).type == not_a_symbol) {
        fprintf(stderr, "Line %d: class(type) %s is not defined\n", get_line_number(), type_name->get_string());
        class_table->semant_error();
    }
    if (symbol_table->look_up_method(name, type_name).type == not_a_symbol) {
        fprintf(stderr, "Line %d: class(type) %s has no method %s\n", get_line_number(), type_name->get_string(), name->get_string());
        class_table->semant_error();
    }
    /*
      TODO: I am omissing the fact that there could be assignment
      expression in the expression block. Maybe it doesn't matter.
      I will come back later.
   */
    for (int i = actual->first(); actual->more(i); i = actual->next(i)) {
        actual->nth(i)->check_scope_and_type(symbol_table, class_table);
    }
}

void dispatch_class::check_scope_and_type(SymbolTableP symbol_table, ClassTableP class_table) {
    expr->check_scope_and_type(symbol_table, class_table);
    if (symbol_table->look_up_method_self(name).type == not_a_symbol) {
        fprintf(stderr, "Line %d: self has no method %s\n", get_line_number(), name->get_string());
        symbol_table->dump_methods(std::cout);
        class_table->semant_error();
    }
    /*
      TODO: I am omissing the fact that there could be assignment
      expression in the expression block. Maybe it doesn't matter.
      I will come back later.
   */
    for (int i = actual->first(); actual->more(i); i = actual->next(i)) {
        actual->nth(i)->check_scope_and_type(symbol_table, class_table);
    }
}

void cond_class::check_scope_and_type(SymbolTableP symbol_table, ClassTableP class_table) {
    pred->check_scope_and_type(symbol_table, class_table);
    then_exp->check_scope_and_type(symbol_table, class_table);
    else_exp->check_scope_and_type(symbol_table, class_table);
}

void loop_class::check_scope_and_type(SymbolTableP symbol_table, ClassTableP class_table) {
    pred->check_scope_and_type(symbol_table, class_table);
    body->check_scope_and_type(symbol_table, class_table);
}

void typcase_class::check_scope_and_type(SymbolTableP symbol_table, ClassTableP class_table) {
    expr->check_scope_and_type(symbol_table, class_table);
    for (int i = cases->first(); cases->more(i); i = cases->next(i)) {
        static_cast<branch_class *>(cases->nth(i))->check_scope_and_type(symbol_table, class_table);
    }
}

void block_class::check_scope_and_type(SymbolTableP symbol_table, ClassTableP class_table) {
    for (int i = body->first(); body->more(i); i = body->next(i)) {
        body->nth(i)->check_scope_and_type(symbol_table, class_table);
    }
}

void let_class::check_scope_and_type(SymbolTableP symbol_table, ClassTableP class_table) {
    if (symbol_table->look_up_class(type_decl).type == not_a_symbol) {
        fprintf(stderr, "Line %d: class(type) %s is not defined\n", get_line_number(), type_decl->get_string());
        class_table->semant_error();
    }
    init->check_scope_and_type(symbol_table, class_table);
    SymbolTableP new_table(new SymbolTable());
    new_table->parent = symbol_table;
    new_table->add_object(identifier, SymbolData(SymbolType::let_type));
    body->check_scope_and_type(new_table, class_table);
}

void plus_class::check_scope_and_type(SymbolTableP symbol_table, ClassTableP class_table) {
    e1->check_scope_and_type(symbol_table, class_table);
    e2->check_scope_and_type(symbol_table, class_table);
}

void sub_class::check_scope_and_type(SymbolTableP symbol_table, ClassTableP class_table) {
    e1->check_scope_and_type(symbol_table, class_table);
    e2->check_scope_and_type(symbol_table, class_table);
}

void mul_class::check_scope_and_type(SymbolTableP symbol_table, ClassTableP class_table) {
    e1->check_scope_and_type(symbol_table, class_table);
    e2->check_scope_and_type(symbol_table, class_table);
}

void divide_class::check_scope_and_type(SymbolTableP symbol_table, ClassTableP class_table) {
    e1->check_scope_and_type(symbol_table, class_table);
    e2->check_scope_and_type(symbol_table, class_table);
}

void neg_class::check_scope_and_type(SymbolTableP symbol_table, ClassTableP class_table) {
    e1->check_scope_and_type(symbol_table, class_table);
}

void lt_class::check_scope_and_type(SymbolTableP symbol_table, ClassTableP class_table) {
    e1->check_scope_and_type(symbol_table, class_table);
    e2->check_scope_and_type(symbol_table, class_table);
}

void eq_class::check_scope_and_type(SymbolTableP symbol_table, ClassTableP class_table) {
    e1->check_scope_and_type(symbol_table, class_table);
    e2->check_scope_and_type(symbol_table, class_table);
}

void leq_class::check_scope_and_type(SymbolTableP symbol_table, ClassTableP class_table) {
    e1->check_scope_and_type(symbol_table, class_table);
    e2->check_scope_and_type(symbol_table, class_table);
}

void comp_class::check_scope_and_type(SymbolTableP symbol_table, ClassTableP class_table) {
    e1->check_scope_and_type(symbol_table, class_table);
}

void int_const_class::check_scope_and_type(SymbolTableP symbol_table, ClassTableP class_table) {
    // try{
    //    int i = std::stoll(std::string(token->get_string()));
    // }catch(const std::invalid_argument& ia){
    //    fprintf(stderr, "Line %d: invalid integer %s\n",get_line_number(), token->get_string());
    // }
}

void bool_const_class::check_scope_and_type(SymbolTableP symbol_table, ClassTableP class_table) {
}

void string_const_class::check_scope_and_type(SymbolTableP symbol_table, ClassTableP class_table) {
}

void new__class::check_scope_and_type(SymbolTableP symbol_table, ClassTableP class_table) {
    if (symbol_table->look_up_class(type_name).type == not_a_symbol) {
        fprintf(stderr, "Line %d: class(type) %s is not defined\n", get_line_number(), type_name->get_string());
        class_table->semant_error();
    }
}

void isvoid_class::check_scope_and_type(SymbolTableP symbol_table, ClassTableP class_table) {
    e1->check_scope_and_type(symbol_table, class_table);
}

void no_expr_class::check_scope_and_type(SymbolTableP symbol_table, ClassTableP class_table) {
}

void object_class::check_scope_and_type(SymbolTableP symbol_table, ClassTableP class_table) {
    if (symbol_table->look_up_object(name).type == not_a_symbol) {
        fprintf(stderr, "Line %d: object %s is not defined\n", get_line_number(), name->get_string());
        class_table->semant_error();
    }
}