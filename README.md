<div style='width: 100%;' align='center'><img src='cola.svg.png'/></div>

## Cola
> _A component-based programming language._

## Snippet
> Here is what it looks like:

    comp productlist use httplib, json {
        function array<map> get_products {
            return json.parse(httplib.get('http://example.org/products'));
        };

        function array<map> yields {
            return get_products();    
        };
    };


    comp main use productlist {
        function void run {
            foreach (productlist as product) {
                print(product);    
            };
        };
    };

## How to write a component
### The syntax
> The syntax for a component looks like this:  
`comp [NAME] use [DEPENDENCY-LIST] [LBRACE] [RBRACE]`  

    comp mycomponent use somelibrary {
        ...    
    };

### The run-method
> The `run` method in a component can be executed through the `run` statement:

    comp mycomponent {
        function void run {
            print("Hello World!")    
        };
    };

    comp main use mycomponent {
        // run method of `mycomponent` is executed when mounted like this
    };

### The yields-method
> The `yields` method in a component is used to make a component act as if
> it was another data-type. For example:

    comp PI {
        function float yields {
            return 3.14;
        };    
    };

    comp main use PI {
        function void run {
            print(PI * 0.5);    
        };    
    };

> ... here, the `PI` component is treated as if it was a float.

### Interpreter instructions
> You can include other files using interpreter instructions, it looks
> very much like in `C`:

    #include "somefile.cola"


    comp main {
        ...

## Data-types
> The existing data-types are:  
* int
* string
* array
* map
* struct

### Note
> The `array` data-type can hold any sort of type, but the type must
> be specified like: `array<int> numbers;` or `array<string> names;`

> The `map` data-type can also hold any sort of type and specified like:  
> `map<str, int> ages;` or `map<string, array<int>> fav_numbers;`

## Built-in methods
> These are the built-in methods that currently exists:
* **print** - _print something to stdout_ (takes an infinite list of arguments)
