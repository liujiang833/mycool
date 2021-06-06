This design doc is created after my first unsuccessful attempt to build the semantic analyzer.  
Good remark from PA4:  

- What requirements do I need to check? 
- When do I need to check a requirement? 
- When is the information needed to check a requirement generated? 
- Where is the information I need to check a requirement?  

### Problem to sovle:  
- Check is class heirarchy is well-formed. No cycles, restrictions on basic classes.
- Scope check. Check the use of types, methods, and variables are valid.  
- Type checking. Check the type of expressions.  

### Class heirarchy  
First, we need to check there is no cycle in class inheritance. To do so, we need to first build a dependency graph and then check the cycles in the graph. Also, the dependency graph will remain in memory as we need it for type checking.  
We also want to make sure that user-defined classes don't inherits Int, Bool and String. Certainly redefinition of claases are also not allowed.  

#### Design
```
class ClassNode{
    parent pointer
    child pointers
    class node from ast
}
```


### Scope and Type
Scope checking and type checking has to conducted at the same time. When we check if a method call is valid or not, we have to know the type of the expression that initiates the method call. 

Classes and their methods should be visible in global scope.Objects should be introduced in nested scopes. Each symbol table is responsible for storing new symbols introduced in that new scope. Classe level symbol tables exist permanently and local symbol tables are constructed and destroyed as we go. The current scope's symbol table will have a pointer to the symbol table of its parent scope. Since we allow methods and objects to take on the same name, the symbol table will manage objects and methods separately. Note: 
- since symbol table for class is a hash table that maps ```Symbol``` to ```ClassNode```. So we can easily check the existence of class name and access the corresponding nodes in the class dependency graph. This hash table should be produced in previous step where we check cycles of class inheritance.
- SELF_TYPE is a special occasion for type checking and we will have special code to handle it. So it is not in the class symbol table.
- for conveniently finding method call implicitly following self,
each local table would have a pointer to its class-level symbol table
- scope and type checking is done simultaneously in the top-down manner by recursively call ```check_and_annotate``` we will define for each node class in this part of the project.
- When we a function has invalid type, that type is replaced by object type.
#### Design

```c++
// we also reuse class table to allow fast access of nodes
// in class dependency graph
HashSet[Symbol -> ClassNode] class_table;
HashTable[Symbol -> SymbolTable] class_level_tables;
SymbolTable t1, t2,t3, ... tn;
t1 <- t2 <- t3 <- ... <- tn;

class SymbolTable{
    parent table
     //if it's not a class table we will not bother to find method in it
    Symbol class_name
    is_class_table
    class_level table
    methods
    objects
}

struct Info{
    type // return type for method and actual type for objects
    formals // formal parameters for methods
}
```
#### Algorithm
```
Build global table:
for class in classes(sorted in topological order):
    create new table for the class c
    if class has parent class:
        look up parent class symbol table p
        point c to p
    for attribute in class attributes:
        check redefinition
        check type
        add attribute to table
    add self:class_name to table
    for method in class methods:
        if parent has the method:
            check parameters being the same
        else
            check redefinition
            check parameters being valid
        add method to the table
```