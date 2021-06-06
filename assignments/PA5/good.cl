class C {
	a : Int <- 128 * 3;
	b : Bool <-  not true;
	init(x : Int, y : Bool, z:Int) : C {
           {
		a <- x;
		b <- y;
        z <-  let a:Int <- 5 in a <-a + 1;
		self;
           }
	};
};

Class Main {
	main():C {
	  (new C).init(1,true,1)
	};
};
