function fib(num1,num2,max) -> {
    if(num1+num2 < max) -> {
        print -> num1+num2;
        fib(num1+num2,num1,max);
    }
}
fib -> (0,1,100);