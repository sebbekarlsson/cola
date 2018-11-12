<div style='width: 100%;' align='center'><img src='cola.svg.png'/></div>

## Cola
> _A component-based programming language._

## Snippet
> Here is what it looks like:

    comp productlist use httplib, json {
        array<map> get_products {
            return json.parse(httplib.get('http://example.org/products'));
        };

        array<map> yields {
            return @get_products();    
        };
    };


    comp main use productlist {
        void run {
            foreach (product in productlist) {
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
        void run {
            print("Hello World!")    
        };
    };

    comp othercomponent use mycomponent {
        void run {
            run mycomponent;  // will execute `run` method in `mycomponent`
        };
    };

### The yields-method
> The `yields` method in a component is used to make a component act as if
> it was another data-type. For example:

    component PI {
        float yields {
            return 3.14;
        };    
    };

    component main use PI {
        void run {
            print(PI * 0.5);    
        };    
    };

> ... here, the `PI` component is treated as if it was a float.

### The @-character
> The `@` character is exactly like `this` in object-oriented programming
> languages.

## Data-types
> The existing data-types are:  
* int
* string
* array
* map

### Note
> The `array` data-type can hold any sort of type, but the type must
> be specified like: `array<int> numbers;` or `array<string> names;`

> The `map` data-type can also hold any sort of type and specified like:  
> `map<str, int> ages;` or `map<string, array<int>> fav_numbers;`
