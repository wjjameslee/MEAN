Full Stack Development:

        MongoDB stores JSON documents - great for working with the javascript stack

        <Navigate to: cd C:/Windows/Users/J/Desktop/MEAN>

        Command Prompt (Windows): 
            node --version : checks the version of Node installed
            npm --version : checks the package manager for JS
            <Commands>
                node    ---> enters the node shell

                console.log("Hello world!")  // outputs Hello world
                var name = "Simon" // creates a variable, name
                console.log("Hello " + name) // outputs Hello Simon

                Ctrl^c (pressing twice, exits the node shell)


            node [filename] : runs the JS file 
            (eg.) node app.js 
        
        Node.js 

        "require" keyword will load in other scripts
        (eg.) require('./instantHello');  // need to tell Node to look in the current directory 
        (eg.) require('./talk'); // it will first look for an app called talk.js, then if no such file is found it will look for index.js inside the talk folder
        This runs right away... what if we want to run it for specified times? We will look into that later...

        "module.exports" keyword can return a function() and you can reference the function by a require('./filepath')
        (ie.) var next = require(./talk/goodbye);
        Doing so, you can call this function (ie. call goodbye() in the file that required it) and it will run whenever it is called to.

        See code examples for more detailed explanation.
        

        setTimeout.js has created a piece of asynchronous code whilst not interrupting the main process of the code (1, 3, 2)
        Basically, ascynchronous code does not interrupt the flow of code.
        When dealing with anonymous callback functions ESPECIALLY WHEN YOU HAVE LOTS OF CALLBACKS, you cannot do any unit testing on the callback function
        To deal with this, we can use what is known as "named callbacks".


        A "computation blocker" is a process where the code takes quite a while to execute, blocking the main process.
        We want to maintain code that runs straight away, but what if we want to, lets say calculate a large fibonacci number?
        To find out more, look at file: computational_blocking.js
        Solution: call the "child process"; look at file: computational_non_blocking.js
        child_process has two things to consider: the command to run {'node'} and its arguments (eg. files)

        Usage Example:
            var child_process = require('child_process');  
            var newProcess = child_process.spawn('node', ['_fibonacci.js'], {
                stdio : 'inherit'
            });

        (Note: The "child process" runs a separate process so it does not share the same console.log from the file. The fix is shown above.)

        To create an npm from Node, we just type on the command 'npm init'  --> creates a package.json file
        **Not allowed to create an npm file with uppercase letters
        (eg.) npm install express --save
        (eg.) npm install mocha --save-dev

        What if we took files from a github repository where we do not have the required modules?
        How would we want to deal with this specific scenario?

        We can either just run the command 'npm install' to download all the node modules, but what if we want to only get the required dependencies?
        To remove dev dependencies from npm, we can use the command 'npm install --production'.
        To remove the npm warning package.json: "No README data", create a README file (readme.md) and just write some brief mockdown about your app.

        Question: How do we prevent our node_modules folder to be uploaded onto git?
            Create a .gitignore file that has content: "node_modules". This will fix it.

        How to run scripts defined in the package.json file in npm:
            Given our package.json file:
                "scripts": {
                        "start": "node meanapp.js",
                        "test": "echo \"Error: no test specified\" && exit 1"
                    },

            We can type the command 'npm start' to start our meanapp file instead of manually typing in 'node meanapp.js'.