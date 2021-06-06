#ifndef SEMANT_H_
#define SEMANT_H_

#include <assert.h>

#include <iostream>

#include "cool-tree.h"
#include "stringtab.h"
// #include "symtab.h"
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <cool-tree.h>

#include "list.h"

#define TRUE 1
#define FALSE 0

#ifndef symstem_volcab
#define symstem_volcab
#endif
class ClassTable;
typedef ClassTable* ClassTableP;
struct ClassNode;
typedef ClassNode* ClassNodeP;
class SymbolTable;
typedef SymbolTable* SymbolTableP;
struct Info;
typedef Info* InfoP;
class class__class;
class attr_class;
class method_class;

struct ClassNode {
    class__class* value;
    ClassNodeP parent;
    bool inheritable;
    std::vector<ClassNodeP> children;
    ClassNode(class__class* v,ClassNodeP p=nullptr,bool h=true,std::vector<ClassNodeP> c = std::vector<ClassNodeP>())
            :value(v),parent(p),inheritable(h),children(c){}
};

struct Info{
  Symbol type;// class type of the object or return type of the method
  Formals formals;
  Symbol actual_type;
  Info(Symbol t = nullptr, Formals f=nullptr):type(t),formals(f){}
};

class SymbolTable {
   public:
    SymbolTableP parent_table = nullptr;
    std::unordered_map<Symbol, Info> methods;
    std::unordered_map<Symbol, Info> objects;
    Symbol class_name;
    bool is_class_level = false;
    SymbolTable(Symbol c):class_name(c){}
    Info look_up_method(Symbol name);
    Info look_up_object(Symbol name);
    void add_object(Symbol name,Info&& info);
    void add_method(Symbol name,Info&& info);
    SymbolTable(){}
    SymbolTable(SymbolTableP p):parent_table(p){}
    Symbol get_self_type();
};

class ClassTable {
   private:
    //attributes
    int semant_errors;
    ostream& error_stream;

    // helper methods
    void install_classes(Classes classes);
    Classes add_basic_classes(Classes classes);
    //recursively walk through inheritance grah and try to find cycles
    void cycle_dfs(ClassNodeP root, std::unordered_set<ClassNodeP>& visited);
    //recursively build class level symbol table
    void build_class_level_table(ClassNodeP class_node);
    void add_attr(attr_class* attr, SymbolTableP symbol_table,char* filename);
    void add_method(method_class* method, SymbolTableP symbol_table,char*filename);
    bool same_formal(Formals a, Formals b);
    void check_and_remedy(Formals a,char* filename);
    void check_scope_and_type();
    void check_scope_and_type_r(ClassNodeP root);
    void check_main();

   public:
    ClassTable(Classes);
    ~ClassTable();
    int errors() { return semant_errors; }
    ostream& semant_error();
    ostream& semant_error(Class_ c);
    ostream& semant_error(Symbol filename, tree_node* t);
};

#endif
