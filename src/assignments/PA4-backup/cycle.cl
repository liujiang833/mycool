
class A inherits C{

   -- Let's assume that we don't want A to not inherit from IO.

   io : IO <- new IO;

   out_a() : Object { io.out_string("A: Hello world\n") };

};


class B inherits A {

   -- B does not have to an extra attribute, since it inherits io from A.

   out_b() : Object { io.out_string("B: Hello world\n") };

};


class C{
    io: IO <-new IO;
    out_a(): Object{io.out_string("C: Hello world\n")};
};


class Main inherits IO {

   -- Same case as class C.

   main() : Object {
      {
	 (new A).out_a();
	 (new B).out_b();
	 (new C).out_c();
	 out_string("Done.\n");
      }
   };

};
