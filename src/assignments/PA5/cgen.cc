
//**************************************************************
//
// Code generator SKELETON
//
// Read the comments carefully. Make sure to
//    initialize the base class tags in
//       `CgenClassTable::CgenClassTable'
//
//    Add the label for the dispatch tables to
//       `IntEntry::code_def'
//       `StringEntry::code_def'
//       `BoolConst::code_def'
//
//    Add code to emit everyting else that is needed
//       in `CgenClassTable::code'
//
//
// The files as provided will produce code to begin the code
// segments, declare globals, and emit constants.  You must
// fill in the rest.
//
//**************************************************************

#include "cgen.h"

#include "cgen_gc.h"
#include "string"

extern void emit_string_constant(ostream &str, char *s);
extern int cgen_debug;
static int DISPATCH_ABOT = 0;
static int next_label = 10;

//
// Three symbols from the semantic analyzer (semant.cc) are used.
// If e : No_type, then no code is generated for e.
// Special code is generated for new SELF_TYPE.
// The name "self" also generates code different from other references.
//
//////////////////////////////////////////////////////////////////////
//
// Symbols
//
// For convenience, a large number of symbols are predefined here.
// These symbols include the primitive type and method names, as well
// as fixed names used by the runtime system.
//
//////////////////////////////////////////////////////////////////////
Symbol
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

static char *gc_init_names[] =
    {"_NoGC_Init", "_GenGC_Init", "_ScnGC_Init"};
static char *gc_collect_names[] =
    {"_NoGC_Collect", "_GenGC_Collect", "_ScnGC_Collect"};

//  BoolConst is a class that implements code generation for operations
//  on the two booleans, which are given global names here.
BoolConst falsebool(FALSE);
BoolConst truebool(TRUE);

//*********************************************************
//
// Define method for code generation
//
// This is the method called by the compiler driver
// `cgtest.cc'. cgen takes an `ostream' to which the assembly will be
// emmitted, and it passes this and the class list of the
// code generator tree to the constructor for `CgenClassTable'.
// That constructor performs all of the work of the code
// generator.
//
//*********************************************************

void CgenClassTable::build_class_layout(CgenNodeP root) {
    auto parentnd = root->get_parentnd();
    ClassLayout curr_layout;
    if (parentnd != nullptr) {
        curr_layout = class_layouts[parentnd->get_name()];
    }
    // add additional features to end of parent layout
    Features features = root->features;
    for (int i = features->first(); features->more(i); i = features->next(i)) {
        Feature feature = features->nth(i);
        if (typeid(*feature) == typeid(attr_class)) {
            attr_class *attr = (attr_class *)feature;
            curr_layout.add_attr(attr->name, attr->type_decl, attr);
        }
    }
    class_layouts[root->name] = curr_layout;
    // recursively construct class_layout for child classes
    auto children = root->get_children();
    while (children != nullptr) {
        CgenNode *child = children->hd();
        build_class_layout(child);
        children = children->tl();
    }
}

void CgenClassTable::build_class_method(CgenNodeP root) {
    if (root->parent != nullptr) {
        class_methods[root->name] = class_methods[root->get_parent()];
    }

    int offset = 4 * class_methods[root->name].methods.size();
    Features features = root->features;
    for (int i = features->first(); features->more(i); i = features->next(i)) {
        Feature feature = features->nth(i);
        if (typeid(*feature) == typeid(method_class)) {
            method_class *method = (method_class *)feature;
            class_methods[root->name].add_method(root->name, method);
            method_offsets[root->name][method->name] = offset;
            offset += 4;
        }
    }
    auto children = root->get_children();
    while (children != nullptr) {
        CgenNode *child = children->hd();
        build_class_method(child);
        children = children->tl();
    }
}

void ClassLayout::add_attr(Symbol name, Symbol type, attr_class *attr) {
    linear_layout.push_back({name, type, attr});
    num_attr++;
}

int ClassLayout::attr_pos(Symbol name) {
    for (int i = 0; i < linear_layout.size(); i++) {
        if (std::get<0>(linear_layout[i]) == name) {
            return i;
        }
    }
    return -1;
}
void ClassMethod::add_method(Symbol classname, method_class *method) {
    for (auto &m : methods) {
        if (std::get<1>(m) == method->name) {
            std::get<0>(m) = classname;
            return;
        }
    }
    methods.push_back({classname, method->name, method});
}

void ObjectTable::add_object(Symbol name, int offset, char *reg) {
    location_map[name] = {offset, reg};
}

std::pair<int, char *> &ObjectTable::get_loc(Symbol name) {
    if (location_map.find(name) != location_map.end()) {
        return location_map[name];
    }
    return parent->get_loc(name);
}

Symbol ObjectTable::get_classname() {
    if (classname != nullptr)
        return classname;
    return parent->classname;
}

void ClassLayout::dump_layout() {
    for (int i = 0; i < linear_layout.size(); i++) {
        auto &attr = linear_layout[i];
        printf("%d: %s %s\n", i, std::get<0>(attr)->get_string(), std::get<1>(attr)->get_string());
    }
    printf("------\n");
}
void program_class::cgen(ostream &os) {
    // spim wants comments to start with '#'
    os << "# start of generated code\n";

    initialize_constants();
    CgenClassTable *codegen_classtable = new CgenClassTable(classes, os);
    os << "\n# end of generated code\n";
}

//////////////////////////////////////////////////////////////////////////////
//
//  emit_* procedures
//
//  emit_X  writes code for operation "X" to the output stream.
//  There is an emit_X for each opcode X, as well as emit_ functions
//  for generating names according to the naming conventions (see emit.h)
//  and calls to support functions defined in the trap handler.
//
//  Register names and addresses are passed as strings.  See `emit.h'
//  for symbolic names you can use to refer to the strings.
//
//////////////////////////////////////////////////////////////////////////////

static void emit_load(char *dest_reg, int offset, char *source_reg, ostream &s) {
    s << LW << dest_reg << " " << offset  << "(" << source_reg << ")"
      << endl;
}
// static void emit_load(char *dest_reg, int offset, char *source_reg, ostream &s) {
//     s << LW << dest_reg << " " << offset * WORD_SIZE << "(" << source_reg << ")"
//       << endl;
// }

static void emit_store(char *source_reg, int offset, char *dest_reg, ostream &s) {
    s << SW << source_reg << " " << offset << "(" << dest_reg << ")"
      << endl;
}
// static void emit_store(char *source_reg, int offset, char *dest_reg, ostream &s) {
//     s << SW << source_reg << " " << offset * WORD_SIZE << "(" << dest_reg << ")"
//       << endl;
// }

static void emit_load_imm(char *dest_reg, int val, ostream &s) { s << LI << dest_reg << " " << val << endl; }

static void emit_load_address(char *dest_reg, char *address, ostream &s) { s << LA << dest_reg << " " << address << endl; }

static void emit_partial_load_address(char *dest_reg, ostream &s) { s << LA << dest_reg << " "; }

static void emit_load_bool(char *dest, const BoolConst &b, ostream &s) {
    emit_partial_load_address(dest, s);
    b.code_ref(s);
    s << endl;
}

static void emit_load_string(char *dest, StringEntry *str, ostream &s) {
    emit_partial_load_address(dest, s);
    str->code_ref(s);
    s << endl;
}

static void emit_load_int(char *dest, IntEntry *i, ostream &s) {
    emit_partial_load_address(dest, s);
    i->code_ref(s);
    s << endl;
}

static void emit_move(char *dest_reg, char *source_reg, ostream &s) { s << MOVE << dest_reg << " " << source_reg << endl; }

static void emit_neg(char *dest, char *src1, ostream &s) { s << NEG << dest << " " << src1 << endl; }

static void emit_add(char *dest, char *src1, char *src2, ostream &s) { s << ADD << dest << " " << src1 << " " << src2 << endl; }
static void emit_xor(char *dest, char *src1, char *src2, ostream &s) { s << "\txor\t" << dest << " " << src1 << " " << src2 << endl; }

static void emit_addu(char *dest, char *src1, char *src2, ostream &s) { s << ADDU << dest << " " << src1 << " " << src2 << endl; }

static void emit_addiu(char *dest, char *src1, int imm, ostream &s) { s << ADDIU << dest << " " << src1 << " " << imm << endl; }

static void emit_div(char *dest, char *src1, char *src2, ostream &s) { s << DIV << dest << " " << src1 << " " << src2 << endl; }

static void emit_mul(char *dest, char *src1, char *src2, ostream &s) { s << MUL << dest << " " << src1 << " " << src2 << endl; }

static void emit_sub(char *dest, char *src1, char *src2, ostream &s) { s << SUB << dest << " " << src1 << " " << src2 << endl; }

static void emit_sll(char *dest, char *src1, int num, ostream &s) { s << SLL << dest << " " << src1 << " " << num << endl; }

static void emit_jalr(char *dest, ostream &s) { s << JALR << "\t" << dest << endl; }

static void emit_jal(char *address, ostream &s) { s << JAL << address << endl; }

static void emit_return(ostream &s) { s << RET << endl; }

static void emit_gc_assign(ostream &s) { s << JAL << "_GenGC_Assign" << endl; }

static void emit_disptable_ref(Symbol sym, ostream &s) { s << sym << DISPTAB_SUFFIX; }

static void emit_init_ref(Symbol sym, ostream &s) { s << sym << CLASSINIT_SUFFIX; }

static void emit_label_ref(int l, ostream &s) { s << "label" << l; }

static void emit_protobj_ref(Symbol sym, ostream &s) { s << sym << PROTOBJ_SUFFIX; }

static void emit_method_ref(Symbol classname, Symbol methodname, ostream &s) { s << classname << METHOD_SEP << methodname; }

static void emit_label_def(int l, ostream &s) {
    emit_label_ref(l, s);
    s << ":" << endl;
}

static void emit_beqz(char *source, int label, ostream &s) {
    s << BEQZ << source << " ";
    emit_label_ref(label, s);
    s << endl;
}

static void emit_beq(char *src1, char *src2, int label, ostream &s) {
    s << BEQ << src1 << " " << src2 << " ";
    emit_label_ref(label, s);
    s << endl;
}

static void emit_bne(char *src1, char *src2, int label, ostream &s) {
    s << BNE << src1 << " " << src2 << " ";
    emit_label_ref(label, s);
    s << endl;
}

static void emit_bleq(char *src1, char *src2, int label, ostream &s) {
    s << BLEQ << src1 << " " << src2 << " ";
    emit_label_ref(label, s);
    s << endl;
}

static void emit_blt(char *src1, char *src2, int label, ostream &s) {
    s << BLT << src1 << " " << src2 << " ";
    emit_label_ref(label, s);
    s << endl;
}

static void emit_blti(char *src1, int imm, int label, ostream &s) {
    s << BLT << src1 << " " << imm << " ";
    emit_label_ref(label, s);
    s << endl;
}

static void emit_bgti(char *src1, int imm, int label, ostream &s) {
    s << BGT << src1 << " " << imm << " ";
    emit_label_ref(label, s);
    s << endl;
}

static void emit_branch(int l, ostream &s) {
    s << BRANCH;
    emit_label_ref(l, s);
    s << endl;
}

//
// Push a register on the stack. The stack grows towards smaller addresses.
//
static void emit_push(char *reg, ostream &str) {
    emit_store(reg, 0, SP, str);
    emit_addiu(SP, SP, -4, str);
}

//
// Fetch the integer value in an Int object.
// Emits code to fetch the integer value of the Integer object pointed
// to by register source into the register dest
//
static void emit_fetch_int(char *dest, char *source, ostream &s) { emit_load(dest, DEFAULT_OBJFIELDS, source, s); }

//
// Emits code to store the integer value contained in register source
// into the Integer object pointed to by dest.
//
static void emit_store_int(char *source, char *dest, ostream &s) { emit_store(source, DEFAULT_OBJFIELDS, dest, s); }

static void emit_test_collector(ostream &s) {
    emit_push(ACC, s);
    emit_move(ACC, SP, s);   // stack end
    emit_move(A1, ZERO, s);  // allocate nothing
    s << JAL << gc_collect_names[cgen_Memmgr] << endl;
    emit_addiu(SP, SP, 4, s);
    emit_load(ACC, 0, SP, s);
}

static void emit_gc_check(char *source, ostream &s) {
    if (source != (char *)A1) emit_move(A1, source, s);
    s << JAL << "_gc_check" << endl;
}

///////////////////////////////////////////////////////////////////////////////
//
// coding strings, ints, and booleans
//
// Cool has three kinds of constants: strings, ints, and booleans.
// This section defines code generation for each type.
//
// All string constants are listed in the global "stringtable" and have
// type StringEntry.  StringEntry methods are defined both for String
// constant definitions and references.
//
// All integer constants are listed in the global "inttable" and have
// type IntEntry.  IntEntry methods are defined for Int
// constant definitions and references.
//
// Since there are only two Bool values, there is no need for a table.
// The two booleans are represented by instances of the class BoolConst,
// which defines the definition and reference methods for Bools.
//
///////////////////////////////////////////////////////////////////////////////

//
// Strings
//
void StringEntry::code_ref(ostream &s) {
    s << STRCONST_PREFIX << index;
}

//
// Emit code for a constant String.
// You should fill in the code naming the dispatch table.
//

void StringEntry::code_def(ostream &s, int stringclasstag) {
    IntEntryP lensym = inttable.add_int(len);

    // Add -1 eye catcher
    s << WORD << "-1" << endl;

    code_ref(s);
    s << LABEL                                                               // label
      << WORD << stringclasstag << endl                                      // tag
      << WORD << (DEFAULT_OBJFIELDS + STRING_SLOTS + (len + 4) / 4) << endl  // size
      << WORD;

    /***** Add dispatch information for class String ******/
    s << "String" << DISPTAB_SUFFIX;
    s << endl;  // dispatch table
    s << WORD;
    lensym->code_ref(s);
    s << endl;                     // string length
    emit_string_constant(s, str);  // ascii string
    s << ALIGN;                    // align to word
}

//
// StrTable::code_string
// Generate a string object definition for every string constant in the
// stringtable.
//
void StrTable::code_string_table(ostream &s, int stringclasstag) {
    for (List<StringEntry> *l = tbl; l; l = l->tl())
        l->hd()->code_def(s, stringclasstag);
}

//
// Ints
//
void IntEntry::code_ref(ostream &s) {
    s << INTCONST_PREFIX << index;
}

//
// Emit code for a constant Integer.
// You should fill in the code naming the dispatch table.
//

void IntEntry::code_def(ostream &s, int intclasstag) {
    // Add -1 eye catcher
    s << WORD << "-1" << endl;

    code_ref(s);
    s << LABEL                                            // label
      << WORD << intclasstag << endl                      // class tag
      << WORD << (DEFAULT_OBJFIELDS + INT_SLOTS) << endl  // object size
      << WORD;

    /***** Add dispatch information for class Int ******/
    s << "Int" << DISPTAB_SUFFIX;
    s << endl;                 // dispatch table
    s << WORD << str << endl;  // integer value
}

//
// IntTable::code_string_table
// Generate an Int object definition for every Int constant in the
// inttable.
//
void IntTable::code_string_table(ostream &s, int intclasstag) {
    for (List<IntEntry> *l = tbl; l; l = l->tl())
        l->hd()->code_def(s, intclasstag);
}

//
// Bools
//
BoolConst::BoolConst(int i) : val(i) { assert(i == 0 || i == 1); }

void BoolConst::code_ref(ostream &s) const {
    s << BOOLCONST_PREFIX << val;
}

//
// Emit code for a constant Bool.
// You should fill in the code naming the dispatch table.
//

void BoolConst::code_def(ostream &s, int boolclasstag) {
    // Add -1 eye catcher
    s << WORD << "-1" << endl;

    code_ref(s);
    s << LABEL                                             // label
      << WORD << boolclasstag << endl                      // class tag
      << WORD << (DEFAULT_OBJFIELDS + BOOL_SLOTS) << endl  // object size
      << WORD;

    /***** Add dispatch information for class Bool ******/
    s << "Bool" << DISPTAB_SUFFIX;
    s << endl;                 // dispatch table
    s << WORD << val << endl;  // value (0 or 1)
}

//////////////////////////////////////////////////////////////////////////////
//
//  CgenClassTable methods
//
//////////////////////////////////////////////////////////////////////////////

//***************************************************
//
//  Emit code to start the .data segment and to
//  declare the global names.
//
//***************************************************

void CgenClassTable::code_global_data() {
    Symbol main = idtable.lookup_string(MAINNAME);
    Symbol string = idtable.lookup_string(STRINGNAME);
    Symbol integer = idtable.lookup_string(INTNAME);
    Symbol boolc = idtable.lookup_string(BOOLNAME);

    str << "\t.data\n"
        << ALIGN;
    //
    // The following global names must be defined first.
    //
    str << GLOBAL << CLASSNAMETAB << endl;
    str << GLOBAL;
    emit_protobj_ref(main, str);
    str << endl;
    str << GLOBAL;
    emit_protobj_ref(integer, str);
    str << endl;
    str << GLOBAL;
    emit_protobj_ref(string, str);
    str << endl;
    str << GLOBAL;
    falsebool.code_ref(str);
    str << endl;
    str << GLOBAL;
    truebool.code_ref(str);
    str << endl;
    str << GLOBAL << INTTAG << endl;
    str << GLOBAL << BOOLTAG << endl;
    str << GLOBAL << STRINGTAG << endl;

    //
    // We also need to know the tag of the Int, String, and Bool classes
    // during code generation.
    //
    str << INTTAG << LABEL
        << WORD << intclasstag << endl;
    str << BOOLTAG << LABEL
        << WORD << boolclasstag << endl;
    str << STRINGTAG << LABEL
        << WORD << stringclasstag << endl;
}

//***************************************************
//
//  Emit code to start the .text segment and to
//  declare the global names.
//
//***************************************************

void CgenClassTable::code_global_text() {
    str << GLOBAL << HEAP_START << endl
        << HEAP_START << LABEL
        << WORD << 0 << endl
        << "\t.text" << endl
        << GLOBAL;
    emit_init_ref(idtable.add_string("Main"), str);
    str << endl
        << GLOBAL;
    emit_init_ref(idtable.add_string("Int"), str);
    str << endl
        << GLOBAL;
    emit_init_ref(idtable.add_string("String"), str);
    str << endl
        << GLOBAL;
    emit_init_ref(idtable.add_string("Bool"), str);
    str << endl
        << GLOBAL;
    emit_method_ref(idtable.add_string("Main"), idtable.add_string("main"), str);
    str << endl;
}

void CgenClassTable::code_bools(int boolclasstag) {
    falsebool.code_def(str, boolclasstag);
    truebool.code_def(str, boolclasstag);
}

void CgenClassTable::code_select_gc() {
    //
    // Generate GC choice constants (pointers to GC functions)
    //
    str << GLOBAL << "_MemMgr_INITIALIZER" << endl;
    str << "_MemMgr_INITIALIZER:" << endl;
    str << WORD << gc_init_names[cgen_Memmgr] << endl;
    str << GLOBAL << "_MemMgr_COLLECTOR" << endl;
    str << "_MemMgr_COLLECTOR:" << endl;
    str << WORD << gc_collect_names[cgen_Memmgr] << endl;
    str << GLOBAL << "_MemMgr_TEST" << endl;
    str << "_MemMgr_TEST:" << endl;
    str << WORD << (cgen_Memmgr_Test == GC_TEST) << endl;
}

//********************************************************
//
// Emit code to reserve space for and initialize all of
// the constants.  Class names should have been added to
// the string table (in the supplied code, is is done
// during the construction of the inheritance graph), and
// code for emitting string constants as a side effect adds
// the string's length to the integer table.  The constants
// are emmitted by running through the stringtable and inttable
// and producing code for each entry.
//
//********************************************************

void CgenClassTable::code_constants() {
    //
    // Add constants that are required by the code generator.
    //
    stringtable.add_string("");
    inttable.add_string("0");

    stringtable.code_string_table(str, stringclasstag);
    inttable.code_string_table(str, intclasstag);
    code_bools(boolclasstag);
}

CgenClassTable::CgenClassTable(Classes classes, ostream &s) : nds(NULL), str(s) {
    enterscope();
    if (cgen_debug) cout << "Building CgenClassTable" << endl;
    install_basic_classes();
    install_classes(classes);
    build_inheritance_tree();

    build_class_layout(root());
    class_layouts.erase(No_class);
    build_class_method(root());
    assign_class_tags();
    stringclasstag = get_class_tag(idtable.add_string("String"));
    intclasstag = get_class_tag(idtable.add_string("Int"));
    boolclasstag = get_class_tag(idtable.add_string("Bool"));
    // cout << class_layouts.size() << endl;
    // for(auto& p : class_layouts){
    //     printf("Class %s:\n",p.first->get_string());
    //     p.second.dump_layout();
    // }
    // for (auto classname : class_order) {
    //     cout << classname << endl;
    // }
    code();
    exitscope();
}

void CgenClassTable::assign_class_tags() {
    for (auto &p : class_layouts) {
        class_order.push_back(p.first);
    }
}

int get_class_tag(Symbol classname) {
    for (int i = 0; i < class_order.size(); i++) {
        if (class_order[i] == classname)
            return i;
    }
    return -1;
}
void CgenClassTable::code_class_nameTab() {
    str << CLASSNAMETAB << ":" << endl;
    for (auto classname : class_order) {
        str << WORD << STRCONST_PREFIX << get_str_const_index(classname) << endl;
    }
}
void CgenClassTable::code_dispatch_tables() {
    str << CLASSOBJTAB << ":\n";
    for (auto classname : class_order) {
        str << WORD << classname << PROTOBJ_SUFFIX << endl;
        str << WORD << classname << CLASSINIT_SUFFIX << endl;
    }
    for (auto classname : class_order) {
        code_dispatch_table(classname);
    }
}

void CgenClassTable::code_dispatch_table(Symbol classname) {
    auto class_method = class_methods[classname];
    str << classname << DISPTAB_SUFFIX << ":\n";
    for (auto p : class_method.methods) {
        str << WORD << std::get<0>(p) << "." << std::get<1>(p) << endl;
    }
}

void CgenClassTable::code_prototype_objects() {
    for (auto classname : class_order) {
        code_prototype_object(classname);
    }
}

void CgenClassTable::code_prototype_object(Symbol classname) {
    auto &class_layout = class_layouts[classname];
    //gc bit
    str << WORD << -1 << endl;
    //label
    str << classname << PROTOBJ_SUFFIX << ":\n";
    // class tag
    str << WORD << get_class_tag(classname) << endl;
    int attr_num = class_layout.linear_layout.size();
    // object size
    str << WORD << 3 + attr_num << endl;
    // dispatch pointer
    str << WORD << classname << DISPTAB_SUFFIX << endl;
    //attributes
    for (auto &p : class_layout.linear_layout) {
        str << WORD;
        if (std::get<1>(p) == idtable.add_string("Int")) {
            str << INTCONST_PREFIX << get_int_const_index(inttable.add_int(0));
        } else if (std::get<1>(p) == idtable.add_string("String")) {
            str << STRCONST_PREFIX << get_str_const_index(stringtable.add_string(""));
        } else if (std::get<1>(p) == idtable.add_string("Bool")) {
            str << BOOLCONST_PREFIX << 0;
        } else {
            str << 0;
        }
        str << endl;
    }
}
void CgenClassTable::code_class_inits() {
    for (auto classname : class_order) {
        code_class_init(classname);
    }
}

void CgenClassTable::code_class_init(Symbol classname) {
    auto curr_node = probe(classname);
    auto parent_name = curr_node->get_parent();
    str << classname << CLASSINIT_SUFFIX << ":\n";
    emit_addiu(SP, SP, -12, str);
    emit_store(FP, 12, SP, str);
    emit_store(SELF, 8, SP, str);
    emit_store(RA, 4, SP, str);
    emit_move(SELF, ACC, str);
    if (classname != Object) {
        std::string parent_init = std::string(parent_name->get_string()) + std::string(CLASSINIT_SUFFIX);
        emit_jal((char *)parent_init.c_str(), str);
    }
    ClassLayout &curr_layout = class_layouts[classname];

    int offset = 12;
    for (auto &attr_info : curr_layout.linear_layout) {
        // load self to $a0
        attr_class *attr = std::get<2>(attr_info);
        // if attr init body is not empty
        if (attr->init != nullptr) {
            emit_move(ACC, SELF, str);
            attr->init->object_table = new ObjectTable();
            attr->init->code(str);
            emit_store(ACC, offset, SELF, str);
        }
        offset += 4;
    }
    emit_load(FP, 12, SP, str);
    emit_load(SELF, 8, SP, str);
    emit_load(RA, 4, SP, str);
    emit_addiu(SP, SP, 12, str);
    str << RA << endl;
}

void CgenClassTable::code_all_class_methods() {
    code_class_methods(root());
}

void CgenClassTable::code_class_methods(CgenNodeP root) {
    Features features = root->features;
    for(int i=features->first(); features->more(i); i = features->next(i)){
        Feature feature = features->nth(i);
        if(typeid(*feature) == typeid(method_class*)){
            method_class* method = (method_class*)feature;
            method->code(str,root->name);
        }
    }
    auto children = root->get_children();
    while (children != nullptr) {
        CgenNode *child = children->hd();
        code_class_methods(child);
        children = children->tl();
    }

}
int get_str_const_index(Symbol classname) {
    for (int i = stringtable.first(); stringtable.more(i); i = stringtable.next(i)) {
        auto entry = stringtable.lookup(i);
        if (entry->equal_string(classname->get_string(), classname->get_len())) {
            return i;
        }
    }
    return -1;
}

int get_int_const_index(Symbol intval) {
    for (int i = inttable.first(); inttable.more(i); i = inttable.next(i)) {
        auto entry = inttable.lookup(i);
        if (entry->equal_string(intval->get_string(), intval->get_len())) {
            return i;
        }
    }
    return -1;
}
void CgenClassTable::install_basic_classes() {
    // The tree package uses these globals to annotate the classes built below.
    //curr_lineno  = 0;
    Symbol filename = stringtable.add_string("<basic class>");

    //
    // A few special class names are installed in the lookup table but not
    // the class list.  Thus, these classes exist, but are not part of the
    // inheritance hierarchy.
    // No_class serves as the parent of Object and the other special classes.
    // SELF_TYPE is the self class; it cannot be redefined or inherited.
    // prim_slot is a class known to the code generator.
    //
    addid(No_class,
          new CgenNode(class_(No_class, No_class, nil_Features(), filename),
                       Basic, this));
    addid(SELF_TYPE,
          new CgenNode(class_(SELF_TYPE, No_class, nil_Features(), filename),
                       Basic, this));
    addid(prim_slot,
          new CgenNode(class_(prim_slot, No_class, nil_Features(), filename),
                       Basic, this));

    //
    // The Object class has no parent class. Its methods are
    //        cool_abort() : Object    aborts the program
    //        type_name() : Str        returns a string representation of class name
    //        copy() : SELF_TYPE       returns a copy of the object
    //
    // There is no need for method bodies in the basic classes---these
    // are already built in to the runtime system.
    //
    install_class(
        new CgenNode(
            class_(Object,
                   No_class,
                   append_Features(
                       append_Features(
                           single_Features(method(cool_abort, nil_Formals(), Object, no_expr())),
                           single_Features(method(type_name, nil_Formals(), Str, no_expr()))),
                       single_Features(method(copy, nil_Formals(), SELF_TYPE, no_expr()))),
                   filename),
            Basic, this));

    //
    // The IO class inherits from Object. Its methods are
    //        out_string(Str) : SELF_TYPE          writes a string to the output
    //        out_int(Int) : SELF_TYPE               "    an int    "  "     "
    //        in_string() : Str                    reads a string from the input
    //        in_int() : Int                         "   an int     "  "     "
    //
    install_class(
        new CgenNode(
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
                   filename),
            Basic, this));

    //
    // The Int class has no methods and only a single attribute, the
    // "val" for the integer.
    //
    install_class(
        new CgenNode(
            class_(Int,
                   Object,
                   single_Features(attr(val, prim_slot, no_expr())),
                   filename),
            Basic, this));

    //
    // Bool also has only the "val" slot.
    //
    install_class(
        new CgenNode(
            class_(Bool, Object, single_Features(attr(val, prim_slot, no_expr())), filename),
            Basic, this));

    //
    // The class Str has a number of slots and operations:
    //       val                                  ???
    //       str_field                            the string itself
    //       length() : Int                       length of the string
    //       concat(arg: Str) : Str               string concatenation
    //       substr(arg: Int, arg2: Int): Str     substring
    //
    install_class(
        new CgenNode(
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
                   filename),
            Basic, this));
}

// CgenClassTable::install_class
// CgenClassTable::install_classes
//
// install_classes enters a list of classes in the symbol table.
//
void CgenClassTable::install_class(CgenNodeP nd) {
    Symbol name = nd->get_name();

    if (probe(name)) {
        return;
    }

    // The class name is legal, so add it to the list of classes
    // and the symbol table.
    nds = new List<CgenNode>(nd, nds);
    addid(name, nd);
}

void CgenClassTable::install_classes(Classes cs) {
    for (int i = cs->first(); cs->more(i); i = cs->next(i))
        install_class(new CgenNode(cs->nth(i), NotBasic, this));
}

//
// CgenClassTable::build_inheritance_tree
//
void CgenClassTable::build_inheritance_tree() {
    for (List<CgenNode> *l = nds; l; l = l->tl())
        set_relations(l->hd());
}

//
// CgenClassTable::set_relations
//
// Takes a CgenNode and locates its, and its parent's, inheritance nodes
// via the class table.  Parent and child pointers are added as appropriate.
//
void CgenClassTable::set_relations(CgenNodeP nd) {
    CgenNode *parent_node = probe(nd->get_parent());
    nd->set_parentnd(parent_node);
    parent_node->add_child(nd);
}

void CgenNode::add_child(CgenNodeP n) {
    children = new List<CgenNode>(n, children);
}

void CgenNode::set_parentnd(CgenNodeP p) {
    assert(parentnd == NULL);
    assert(p != NULL);
    parentnd = p;
}

void CgenClassTable::code() {
    if (cgen_debug) cout << "coding global data" << endl;
    code_global_data();

    if (cgen_debug) cout << "choosing gc" << endl;
    code_select_gc();

    if (cgen_debug) cout << "coding constants" << endl;
    code_constants();

    code_class_nameTab();
    code_dispatch_tables();
    code_prototype_objects();

    if (cgen_debug) cout << "coding global text" << endl;
    code_global_text();
    code_class_inits();  //TODO: not sure if it works or not
    code_all_class_methods();

    std::cout << "Code generation finished\n";
}

CgenNodeP CgenClassTable::root() {
    return probe(Object);
}

///////////////////////////////////////////////////////////////////////
//
// CgenNode methods
//
///////////////////////////////////////////////////////////////////////

CgenNode::CgenNode(Class_ nd, Basicness bstatus, CgenClassTableP ct) : class__class((const class__class &)*nd),
                                                                       parentnd(NULL),
                                                                       children(NULL),
                                                                       basic_status(bstatus) {
    stringtable.add_string(name->get_string());  // Add class name to string table
}

//******************************************************************
//
//   Fill in the following methods to produce code for the
//   appropriate expression.  You may add or remove parameters
//   as you wish, but if you do, remember to change the parameters
//   of the declarations in `cool-tree.h'  Sample code for
//   constant integers, strings, and booleans are provided.
//
//*****************************************************************

void assign_class::code(ostream &s) {
    expr->code(s);
    auto &offset_reg = object_table->get_loc(name);
    emit_store(ACC, offset_reg.first, offset_reg.second, s);
}

void static_dispatch_class::code(ostream &s) {
    // push arguments
    for (int i = actual->first(); actual->more(i); i = actual->next(i)) {
        Expression one_expr = actual->nth(i);
        one_expr->code(s);
        emit_store(ACC, 0, SP, s);
        emit_addiu(SP, SP, -4, s);
    }
    expr->object_table = object_table;
    //we are moving away from fp
    expr->object_table->fp_offset += actual->len() * 4;
    expr->code(s);
    emit_beq(ACC, ZERO, DISPATCH_ABOT, s);
    std::string method = std::string(type_name->get_string()) + "." + std::string(name->get_string());
    emit_jal((char *)method.c_str(), s);
}

void dispatch_class::code(ostream &s) {
    for (int i = actual->first(); actual->more(i); i = actual->next(i)) {
        Expression one_expr = actual->nth(i);
        one_expr->code(s);
        emit_store(ACC, 0, SP, s);
        emit_addiu(SP, SP, -4, s);
    }
    expr->object_table = object_table;
    //we are moving away from fp
    expr->object_table->fp_offset += actual->len() * 4;
    expr->code(s);
    //TODO: need to write code for dispach on void
    emit_beq(ACC, ZERO, DISPATCH_ABOT, s);
    emit_load(T1, 8, ACC, s);
    emit_load(T1, method_offsets[object_table->get_classname()][name], T1, s);
    emit_jalr(T1, s);
    // restore stack
    emit_addiu(SP, SP, actual->len() * 4, s);
}

void cond_class::code(ostream &s) {
    pred->object_table = object_table;
    pred->code(s);
    // load actual value of bool object
    emit_load(ACC, 12, ACC, s);
    //jump to false branch
    emit_beq(ACC, ZERO, next_label, s);
    then_exp->object_table = object_table;
    then_exp->code(s);
    //jump to escape point
    emit_branch(next_label + 1, s);
    //false branch
    emit_label_def(next_label++, s);
    else_exp->object_table = object_table;
    else_exp->code(s);
    //escape point
    emit_label_def(next_label++, s);
}

void loop_class::code(ostream &s) {
    // entry point of loop
    emit_label_def(next_label++, s);

    // compute predicate
    pred->object_table = object_table;
    pred->code(s);
    emit_load(ACC, 12, ACC, s);
    emit_beq(ACC, ZERO, next_label, s);
    // loop body
    body->object_table = object_table;
    body->code(s);
    //back to entry point
    emit_branch(next_label - 1, s);
    //escape point
    emit_label_def(next_label, s);
}

void typcase_class::code(ostream &s) {
    expr->object_table = object_table;
    expr->code(s);
    //load class tag
    emit_load(T1, 0, ACC, s);
    int escape_offset = cases->len() - 1;
    for (int i = cases->first(); cases->more(i); i = cases->next(i)) {
        branch_class *branch = (branch_class *)cases->nth(i);
        int class_tag = get_class_tag(branch->type_decl);
        emit_label_def(next_label++, s);
        emit_load_imm(T2, class_tag, s);
        emit_bne(T1, T2, next_label, s);
        branch->expr->object_table = object_table;
        branch->expr->code(s);
        emit_branch(next_label + escape_offset, s);
    }
    //escape point
    emit_label_def(next_label++, s);
}

void block_class::code(ostream &s) {
    for (int i = body->first(); body->more(i); i = body->next(i)) {
        Expression expr = body->nth(i);
        expr->object_table = object_table;
        expr->code(s);
    }
}

void let_class::code(ostream &s) {
    init->object_table = object_table;
    object_table = new ObjectTable(object_table);
    object_table->add_object(identifier, object_table->fp_offset, FP);

    // load prototype object
    std::string proto_object = std::string(type_decl->get_string()) + "_" + std::string(PROTOBJ_SUFFIX);
    emit_load_address(ACC, (char *)proto_object.c_str(), s);
    //create a fresh new copy
    emit_jal("Object.copy", s);
    // call default init procedure
    std::string init_address = std::string(type_decl->get_string()) + "_" + std::string(CLASSINIT_SUFFIX);
    emit_jal((char *)init_address.c_str(), s);
    // generate init expression
    // object_table has been injected at first line
    init->code(s);
    emit_push(ACC, s);
    object_table->fp_offset += 4;
    body->object_table = object_table;
    body->code(s);
    //pop stack
    emit_addiu(SP, SP, 4, s);
    object_table->fp_offset -= 4;
}

void plus_class::code(ostream &s) {
    e1->object_table = object_table;
    e1->code(s);
    emit_push(ACC, s);

    e2->object_table = object_table;
    e2->code(s);
    emit_push(ACC, s);

    //create a fresh new int object
    emit_load_int(ACC, inttable.add_int(0), s);
    emit_jal("Object.copy", s);

    // get result of e1 from stack
    emit_load(T2, 8, SP, s);
    // load actual integer to T2
    emit_load(T2, 12, T2, s);
    // get result of e2 from stack
    emit_load(T3, 4, SP, s);
    // load actual integer to T3
    emit_load(T3, 12, T3, s);
    // compute result
    emit_add(T2, T2, T3, s);
    //store result to the new int object
    emit_store(T2, 12, ACC, s);
    // pop stack
    emit_addiu(SP, SP, 8, s);
}

void sub_class::code(ostream &s) {
    e1->object_table = object_table;
    e1->code(s);
    emit_push(ACC, s);

    e2->object_table = object_table;
    e2->code(s);
    emit_push(ACC, s);

    //create a fresh new int object
    emit_load_int(ACC, inttable.add_int(0), s);
    emit_jal("Object.copy", s);

    // get result of e1 from stack
    emit_load(T2, 8, SP, s);
    // load actual integer to T2
    emit_load(T2, 12, T2, s);
    // get result of e2 from stack
    emit_load(T3, 4, SP, s);
    // load actual integer to T3
    emit_load(T3, 12, T3, s);
    // compute result
    emit_sub(T2, T2, T3, s);
    //store result to the new int object
    emit_store(T2, 12, ACC, s);
    // pop stack
    emit_addiu(SP, SP, 8, s);
}

void divide_class::code(ostream &s) {
    e1->object_table = object_table;
    e1->code(s);
    emit_push(ACC, s);

    e2->object_table = object_table;
    e2->code(s);
    emit_push(ACC, s);

    //create a fresh new int object
    emit_load_int(ACC, inttable.add_int(0), s);
    emit_jal("Object.copy", s);

    // get result of e1 from stack
    emit_load(T2, 8, SP, s);
    // load actual integer to T2
    emit_load(T2, 12, T2, s);
    // get result of e2 from stack
    emit_load(T3, 4, SP, s);
    // load actual integer to T3
    emit_load(T3, 12, T3, s);
    // compute result
    emit_div(T2, T2, T3, s);
    //store result to the new int object
    emit_store(T2, 12, ACC, s);
    // pop stack
    emit_addiu(SP, SP, 8, s);
}

void mul_class::code(ostream &s) {
    e1->object_table = object_table;
    e1->code(s);
    emit_push(ACC, s);

    e2->object_table = object_table;
    e2->code(s);
    emit_push(ACC, s);

    //create a fresh new int object
    emit_load_int(ACC, inttable.add_int(0), s);
    emit_jal("Object.copy", s);

    // get result of e1 from stack
    emit_load(T2, 8, SP, s);
    // load actual integer to T2
    emit_load(T2, 12, T2, s);
    // get result of e2 from stack
    emit_load(T3, 4, SP, s);
    // load actual integer to T3
    emit_load(T3, 12, T3, s);
    // compute result
    emit_mul(T2, T2, T3, s);
    //store result to the new int object
    emit_store(T2, 12, ACC, s);
    // pop stack
    emit_addiu(SP, SP, 8, s);
}
void neg_class::code(ostream &s) {
    e1->object_table = object_table;
    e1->code(s);
    // load actual number
    emit_load(T2, 12, ACC, s);
    //create a fresh new int object
    emit_load_int(ACC, inttable.add_int(0), s);
    emit_jal("Object.copy", s);
    //compute negation
    emit_neg(T2, T2, s);
    emit_store(T2, 12, ACC, s);
}

void lt_class::code(ostream &s) {
    e1->object_table = object_table;
    e1->code(s);
    emit_push(ACC, s);
    e2->object_table = object_table;
    e2->code(s);

    //load up e1
    emit_load(T1, 4, SP, s);
    //load up actual value of e1
    emit_load(T1, 12, T1, s);
    //load up actual value of e2
    emit_load(ACC, 12, ACC, s);

    emit_blt(T1, ACC, next_label, s);
    emit_load_bool(ACC, falsebool, s);
    //jump to end
    emit_branch(next_label + 1, s);

    emit_label_def(next_label, s);
    next_label++;
    emit_load_bool(ACC, truebool, s);

    emit_label_def(next_label, s);
    next_label++;
}

void eq_class::code(ostream &s) {
    e1->object_table = object_table;
    e1->code(s);
    emit_move(T1, ACC, s);
    e2->object_table = object_table;
    e2->code(s);
    emit_move(T2, ACC, s);

    //branch value
    emit_load_imm(ACC, 0, s);
    emit_load_imm(A1, 1, s);
    //call equality_test
    emit_jal("equality test", s);
    //result is storen in a0
    emit_beq(ACC, ZERO, next_label, s);
    emit_load_bool(ACC, falsebool, s);
    emit_branch(next_label + 1, s);

    emit_label_def(next_label, s);
    next_label++;
    emit_load_bool(ACC, truebool, s);

    emit_label_def(next_label, s);
    next_label++;
}

void leq_class::code(ostream &s) {
    e1->object_table = object_table;
    e1->code(s);
    emit_push(ACC, s);
    e2->object_table = object_table;
    e2->code(s);

    //load up e1
    emit_load(T1, 4, SP, s);
    //load up actual value of e1
    emit_load(T1, 12, T1, s);
    //load up actual value of e2
    emit_load(ACC, 12, ACC, s);

    emit_blt(T1, ACC, next_label, s);
    emit_load_bool(ACC, falsebool, s);
    //jump to end
    emit_branch(next_label + 1, s);

    emit_label_def(next_label, s);
    next_label++;
    emit_load_bool(ACC, truebool, s);

    emit_label_def(next_label, s);
    next_label++;
}

void comp_class::code(ostream &s) {
    e1->object_table = object_table;
    e1->code(s);

    // load actual value of bool
    emit_load(T1, 12, ACC, s);
    emit_load_imm(T2, -1, s);
    emit_xor(T1, T1, T2, s);
    emit_store(T1, 12, ACC, s);
}

void int_const_class::code(ostream &s) {
    //
    // Need to be sure we have an IntEntry *, not an arbitrary Symbol
    //
    emit_load_int(ACC, inttable.lookup_string(token->get_string()), s);
}

void string_const_class::code(ostream &s) {
    emit_load_string(ACC, stringtable.lookup_string(token->get_string()), s);
}

void bool_const_class::code(ostream &s) {
    emit_load_bool(ACC, BoolConst(val), s);
}

void new__class::code(ostream &s) {
    Symbol type = type_name;
    if (type != SELF_TYPE) {
        std::string address = std::string(type->get_string()) + "." + std::string(PROTOBJ_SUFFIX);
        emit_load_address(ACC, (char *)address.c_str(), s);
        emit_jal("Object.copy", s);
        address = std::string(type->get_string()) + "_" + std::string(CLASSINIT_SUFFIX);
        emit_jal((char *)address.c_str(), s);
    } else {
        // load class tag
        emit_load(T1, 0, SELF, s);
        // find object offset
        emit_load_imm(T2, 8, s);
        emit_mul(T1, T1, T2, s);
        //load base address
        emit_load_address(T3, "class_objTab", s);
        // add offset to base address
        emit_add(ACC, T1, T3, s);
        // store the address
        emit_push(ACC, s);
        // make a new copy
        emit_jal("Object.copy", s);
        emit_load_imm(T2, 4, s);
        //load base address
        emit_load(T1, 4, SP, s);
        //restore stack
        emit_addiu(SP, SP, 4, s);
        //compute init offset
        emit_add(T1, T1, T2, s);
        // call init
        emit_jalr(T1, s);
    }
}

void isvoid_class::code(ostream &s) {
    e1->object_table = object_table;
    e1->code(s);

    emit_beq(ACC, ZERO, next_label, s);
    emit_load_bool(ACC, falsebool, s);
    //jump to end
    emit_branch(next_label + 1, s);

    emit_label_def(next_label, s);
    next_label++;
    emit_load_bool(ACC, truebool, s);
    //end label
    emit_label_def(next_label, s);
    next_label++;
}

void no_expr_class::code(ostream &s) {
}

void object_class::code(ostream &s) {
    auto &offset_src = object_table->get_loc(name);
    emit_load(ACC, offset_src.first, offset_src.second, s);
}

void class__class::code(ostream &s) {
    ObjectTableP object_table = new ObjectTable();
    object_table->classname = name;
    ClassLayout &layout = class_layouts[name];
    int offset = 12;
    for (auto &attr : layout.linear_layout) {
        object_table->add_object(std::get<0>(attr), offset, SELF);
        offset += 4;
    }
    for (int i = features->first(); features->more(i); i = features->next(i)) {
        Feature feature = features->nth(i);
        if (typeid(*feature) == typeid(method_class)) {
            method_class *method = (method_class *)feature;
            method->object_table = object_table;
            method->code(s, name);
        }
    }
}

void method_class::code(ostream &s, Symbol classname) {
    emit_method_ref(classname, name, s);
    s << ":" << endl;
    // introduce new scope
    object_table = new ObjectTable(object_table);
    emit_addiu(SP, SP, -12, s);
    emit_store(FP, 12, SP, s);
    emit_store(SELF, 8, SP, s);
    emit_store(RA, 4, SP, s);

    emit_move(FP, SP, s);
    emit_addiu(FP, FP, formals->len() * 4, s);
    int offset = 0;
    for (int i = formals->first(); formals->more(i); i = formals->next(i)) {
        formal_class *formal = (formal_class *)formals->nth(i);
        object_table->add_object(formal->name, offset, FP);
        offset -= 4;
    }

    expr->object_table = object_table;
    expr->code(s);

    emit_load(FP, 12, SP, s);
    emit_load(SELF, 8, SP, s);
    emit_load(RA, 4, SP, s);
    emit_addiu(SP, SP, 12, s);
    s << RA << endl;
}
