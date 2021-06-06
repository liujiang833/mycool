#ifndef SEMANT_H_
#define SEMANT_H_

#include <assert.h>

#include <iostream>
#include <memory>
#include <string>
#include <typeinfo>
#include <unordered_map>
#include <vector>

#include "cool-tree.h"
#include "list.h"
#include "stringtab.h"

#define TRUE 1
#define FALSE 0

class ClassTable;
typedef ClassTable *ClassTableP;
struct SymbolData;
typedef std::shared_ptr<SymbolData> SymbolDataP;
class SymbolTable;
typedef std::shared_ptr<SymbolTable> SymbolTableP;

enum SymbolType {
    attribute_type,
    parameter_type,
    let_type,
    case_type,
    assign_type,
    class_type,
    method_type,
    no_type,
    not_a_symbol
};
struct SymbolData {
    SymbolType type;
    Symbol return_type;
    Formals formals;
    SymbolData(SymbolType t = SymbolType::not_a_symbol) : type(t) {}
};
class SymbolTable {
   public:
    static Symbol not_a_symbol;
    std::unordered_map<Symbol, SymbolData> objects;
    std::unordered_map<Symbol, SymbolData> methods;
    static std::unordered_map<Symbol, std::unordered_map<Symbol, SymbolData>> global_methods;
    static std::unordered_map<Symbol, std::unordered_map<Symbol, SymbolData>> global_objects;
    static std::unordered_map<Symbol, SymbolData> global_classes;
    friend class ClassTable;
    SymbolTableP parent;
    SymbolTable() {}
    void add_object(Symbol symbol, SymbolData data);
    SymbolData &look_up_object(Symbol symbol);
    SymbolData &look_up_method_self(Symbol symbol);
    SymbolData &look_up_class(Symbol symbol);
    SymbolData &look_up_method(Symbol symbol, Symbol class_);

    static std::string pad(int n);
    static ostream &dump_global(ostream &os);
    int dump_objects(ostream &os);
    int dump_methods(ostream &os);
    ostream &dump(ostream &os);
};

struct ClassNode {
    char *class_name = nullptr;
    ClassNode* parent;
    std::vector<ClassNode *> children;
    char *parent_name = nullptr;
    class__class *value;
    ClassNode(char *name, class__class *val) : class_name(name), value(val) {}
    bool is_parent(ClassNode *);
};

class ClassTable {
   private:
    int semant_errors;
    ClassNode *object_node;
    std::vector<ClassNode *> class_nodes;
    ostream &error_stream;
    Classes classes;
    void install_basic_classes();
    void build_tree();
    void free_tree();
    void check_cycle(ClassNode *root, std::vector<ClassNode *> &visited);
    void check_scope();
    void build_global_table();
    void check_method();
    void check_scope_and_type();
    void topo_sort();
    void add_nodes(std::vector<ClassNode *> &nodes, ClassNode *root);

   public:
    ClassTable(Classes);
    int errors() { return semant_errors; }
    void print_halt() { fprintf(stderr, "Compilation halted due to static semantic errors.\n"); }
    ostream &semant_error();
    ostream &semant_error(Class_ c);
    ostream &semant_error(Symbol filename, tree_node *t);
};

#endif