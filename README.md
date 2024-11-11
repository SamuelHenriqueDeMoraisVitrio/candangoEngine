# Candango Engine Documentation

## Overview

Candango Engine is a lightweight Lua-based engine that allows you to generate dynamic HTML content by embedding Lua commands directly into HTML files. With this engine, you can leverage Lua's logic and functions to create flexible and dynamic web pages.

### Key Features:

- **Lua-powered HTML templating**: Embed Lua variables, functions, and control structures inside HTML.
- **Dynamic rendering**: Render HTML content dynamically by combining static HTML with Lua-based logic.
- **Conditional and loop handling**: Use Lua's control structures for loops and conditionals directly within your templates.

---

## Table of Contents

1. [Setup](#setup)
2. [Basic Usage](#basic-usage)
3. [Template Syntax](#template-syntax)
4. [Commands Overview](#commands-overview)
   - `{}` for variables
   - `{{}}` for control structures (conditions and loops)
   - `{%}` for raw Lua commands
   - `{!}` for functions
5. [Examples](#examples)
   - [Basic Example](#basic-example)
   - [Conditional Statements](#conditional-statements)
   - [Loops](#loops)
   - [Functions](#functions)
6. [Error Handling](#error-handling)
7. [Advanced Features](#advanced-features)
8. [Best Practices](#best-practices)

---

## Setup

To use the Candango Engine in your project, first ensure that the `candango_engine` module is properly installed and available to be required in your Lua environment.

To install Candango Engine in your project, simply copy the command provided in releases and run it within your project, or download the latest version in releases.

### Example Setup

```lua
candango = require("candangoEngine.candango_engine")

local html_content = candango.Render_text(candango.Get_text_by_file_content("templates/index.html"))

if not html_content.exist_error then
    local output_file = io.open("output/index.html", "w")
    output_file:write(html_content.render_text)
    output_file:close()
else
    print(html_content.error_message)
end
```

---

## Basic Usage

### Step 1: Create a Lua file (`main.lua`)

In your Lua script, load the engine, call your template, and specify the desired output.

```lua
candango = require("candangoEngine.candango_engine")

-- Example of setting up variables or functions to use in the HTML template
variables = {
    name = "Samuel",
    age = 25
}

local html = candango.Render_text(candango.Get_text_by_file_content("templates/home.html"))

if not html.exist_error then
    local file = io.open("output/response.html", "w")
    file:write(html.render_text)
    file:close()
    print("HTML generated successfully.")
else
    print(html.error_message)
end
```

### Step 2: Create an HTML template (`home.html`)

Embed Lua logic inside your HTML structure using the syntax provided by the engine.

```html
<html>
    <head>
        <title>My Dynamic Page</title>
    </head>
    <body>
        <h1>Welcome, {variables["name"]}</h1>
        <p>Age: {variables.age}</p>

        {{if variables["age"] >= 18 then}
            <p>You are an adult.</p>
        {%else}
            <p>You are a minor.</p>
        }

    </body>
</html>
```

---

## Template Syntax

The Candango Engine provides special markers to embed Lua commands directly inside HTML.

### **1. Variables:**

Variables can be inserted into your HTML using curly braces `{}`.

```html
<p>Hello, {name}!</p>
```

### **2. Control Structures (if/else, loops):**

Use double curly braces `{{}}` to start a control structure, such as an `if` condition or loop, and `{%}` for other Lua expressions.

#### Conditional:

```html
{{if condition then}
    <p>This will render if the condition is true.</p>
{%else}
    <p>This will render if the condition is false.</p>
}
```

#### Loop:

```html
<ul>
    {{for i = 1, 5 do}
        <li>Item {i}</li>
    }
</ul>
```

### **3. Raw Commands:**

Raw Lua commands can be executed within the HTML using `{%}`.

```html
{%print("This is a raw Lua command executed in the template.")}
```

### **4. Functions:**

Functions can be embedded using `{!}`. This allows you to concatenate function results directly into the HTML.

```html
<p>{!myFunction()}</p>
```

### **5. Creating Variables Inside Templates:**

It is possible to create variables inside the HTML template using `{%}`. However, note that variables declared with `local` within `{%}` blocks **cannot** be used outside that block or shared with the Lua script outside the template.

```html
{%local new_variable = "Test"}
<p>{new_variable}</p> <!-- This will cause an error since "new_variable" is local and cannot be used here -->
```

Additionally, variables used in HTML that are declared externally in Lua (from your `main.lua` script) **must be global**.

Example of a valid global variable:

```lua
-- Declare a global variable
global_variable = "Hello from Lua!"

-- Use it in your template
```

```html
<p>{global_variable}</p>
```

---

## Commands Overview

### `{}`: Embedding Variables

You can reference Lua variables within your HTML templates using `{}`.

```html
<p>My name is {variables["name"]}</p>
```

### `{{}}`: Control Structures

To implement conditionals and loops, use `{{}}` to start the logic block and `{%}` to inject raw Lua code if necessary.

```html
{{if variables["status"] == "active" then}
    <p>Account is active</p>
{%else}
    <p>Account is inactive</p>
}
```

### `{%}`: Raw Lua Commands

For executing raw Lua code that doesn't directly output text, use `{%}`.

```html
{%local x = 5}
```

### `{!}`: Functions

Invoke Lua functions and embed their output using `{!}`.

```html
<p>Result of function: {!myFunction()}</p>
```

---

## Examples

### Basic Example

This example renders a simple HTML page where variables are populated from Lua.

**Lua:**

```lua
candango = require("candangoEngine.candango_engine")
variables = { name = "Samuel", city = "Brasília" }
```

**HTML Template:**

```html
<h1>Hello, {variables["name"]}</h1>
<p>City: {variables["city"]}</p>
```

**Output:**

```html
<h1>Hello, Samuel</h1>
<p>City: Brasília</p>
```

---

### Conditional Statements

**HTML Template:**

```html
{{if variables["age"] >= 18 then}
    <p>Welcome, you are an adult.</p>
{%else}
    <p>Sorry, you are not old enough.</p>
}
```

**Output (if `age >= 18`):**

```html
<p>Welcome, you are an adult.</p>
```

**Output (if `age < 18`):**

```html
<p>Sorry, you are not old enough.</p>
```

---

### Loops

**HTML Template:**

```html
<ul>
    {{for i = 1, 3 do}
        <li>Item {i}</li>
    }
</ul>
```

**Output:**

```html
<ul>
    <li>Item 1</li>
    <li>Item 2</li>
    <li>Item 3</li>
</ul>
```

---

### Functions

**Lua Function:**

```lua
function getMessage()
    return "This is a dynamic message."
end
```

**HTML Template:**

```html
<p>{!getMessage()}</p>
```

**Output:**

```html
<p>This is a dynamic message.</p>
```

---

### Raw text

You can write text without lua formatting. Example:

**Text Template**

```text

My text can be formatted using variables inside curly braces, for example: #{I put the variable in here and I can comment by opening it with '\#' and closing it with '\#/'}#/

```

**Output**

```text

My text can be formatted using variables inside curly braces, for example: {I put the variable in here and I can comment by opening it with '#' and closing it with '#/'}

```

## Error Handling

When rendering a template, the engine provides error handling mechanisms. If an error occurs, the engine returns an error message which can be displayed or logged.

**Lua Example:**

```lua
local text_formated = candango.Render_text(candango.Get_text_by_file_content("template.html"))

if not text_formated.exist_error then
    -- Success
else
    print(text_formated.error_message)
end
```

---

## Advanced Features

- **Custom Commands**: You can extend the template engine to support additional commands and logic. Refer to the source code for further customization options.

---

## Best Practices

- **Keep templates clean**: Avoid overcomplicating templates with too much logic. Keep the logic in Lua and use the templates for rendering.
- **Use global variables with caution**: Remember that only global variables declared in Lua will be accessible in the templates. Local variables inside `{%}` blocks will not be available outside the block.

# LuaCEmbed

---

MIT License

Copyright (c) 2024 Mateus Moutinho Queiroz

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.

