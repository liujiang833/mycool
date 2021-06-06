#include <assert.h>
#include <stdio.h>

#include <unordered_map>
#include <unordered_set>
#include <vector>

#include "cool-tree.h"
#include "emit.h"
#include "symtab.h"

enum Basicness { Basic,
                 NotBasic };
#define TRUE 1
#define FALSE 0

class CgenClassTable;
typedef CgenClassTable* CgenClassTableP;

class CgenNode;
typedef CgenNode* CgenNodeP;
class ObjectTable;
typedef ObjectTable* ObjectTableP;

/* return a map
   class name -> list of attributes
*/
struct ClassLayout;
struct ClassMethod;
/*
   This class abstracts out finding the location 
   of the object in memory. It will be injected to each 
   expression.
*/
class ObjectTable {
   public:
    ObjectTableP parent;
    Symbol classname;
    int fp_offset = 0;  // offset of $sp relative to $fp
    std::unordered_map<Symbol, std::pair<int, char*>> location_map;
    void add_object(Symbol name, int offset, char* reg);
    Symbol get_classname();
    std::pair<int, char*>& get_loc(Symbol name);
    ObjectTable(ObjectTableP p = nullptr) : parent(p) {
        if (p != nullptr)
            fp_offset = parent->fp_offset;
    }
};

struct ClassLayout {
    // <name, type, attr_class>
    std::vector<std::tuple<Symbol, Symbol, attr_class*>> linear_layout;
    int num_attr = 0;

    void add_attr(Symbol name, Symbol type, attr_class* attr);
    int attr_pos(Symbol name);
    void dump_layout();
};

struct ClassMethod {
    std::vector<std::tuple<Symbol, Symbol, method_class*>> methods;
    void add_method(Symbol classname, method_class* method);
};

class CgenClassTable : public SymbolTable<Symbol, CgenNode> {
   private:
    List<CgenNode>* nds;
    ostream& str;
    int stringclasstag;
    int intclasstag;
    int boolclasstag;

    // The following methods emit code for
    // constants and global declarations.

    void code_global_data();
    void code_global_text();
    void code_bools(int);
    void code_select_gc();
    void code_constants();

    // The following creates an inheritance graph from
    // a list of classes.  The graph is implemented as
    // a tree of `CgenNode', and class names are placed
    // in the base class symbol table.

    void install_basic_classes();
    void install_class(CgenNodeP nd);
    void install_classes(Classes cs);
    void build_inheritance_tree();
    void set_relations(CgenNodeP nd);

    void build_class_layout(CgenNodeP root);
    void build_class_method(CgenNodeP root);
    void assign_class_tags();

    void code_class_nameTab();
    void code_dispatch_tables();
    void code_dispatch_table(Symbol classname);
    void code_prototype_objects();
    void code_prototype_object(Symbol classname);
    void code_class_inits();
    void code_class_init(Symbol classname);
    void code_all_class_methods();
    void code_class_methods(CgenNodeP root);

   public:
    CgenClassTable(Classes, ostream& str);
    void code();
    CgenNodeP root();
};

class CgenNode : public class__class {
   private:
    CgenNodeP parentnd;        // Parent of class
    List<CgenNode>* children;  // Children of class
    Basicness basic_status;    // `Basic' if class is basic
                               // `NotBasic' otherwise

   public:
    CgenNode(Class_ c,
             Basicness bstatus,
             CgenClassTableP class_table);

    void add_child(CgenNodeP child);
    List<CgenNode>* get_children() { return children; }
    void set_parentnd(CgenNodeP p);
    CgenNodeP get_parentnd() { return parentnd; }
    int basic() { return (basic_status == Basic); }
};

class BoolConst {
   private:
    int val;

   public:
    BoolConst(int);
    void code_def(ostream&, int boolclasstag);
    void code_ref(ostream&) const;
};

int get_str_const_index(Symbol classname);
int get_int_const_index(Symbol intval);
std::unordered_map<Symbol, ClassLayout> class_layouts;
std::unordered_map<Symbol, ClassMethod> class_methods;
std::vector<Symbol> class_order;
std::unordered_map<Symbol, std::unordered_map<Symbol, int>> method_offsets;
int get_class_tag(Symbol classname);