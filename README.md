# CandangoEngine

**CandangoEngine** is a high-performance templating engine for the Lua programming language, designed with chunk-based rendering capabilities that allow it to efficiently process files even larger than 1GB.

This engine allows developers to dynamically insert Lua logic and variables into plain text files (like HTML) while maintaining blazing speed and flexibility.

---

![Logo do Projeto](assets/imgs/logo_hard.jpeg)

---

## 🚀 Features

* **Variable Interpolation** using `{}`
* **Raw Lua Code Execution** using `#{}`
* **Returnable Lua Code Execution** using `!{}`
* **Ignore Sections** with `$#` and `#$`
* **Chunk-Based Rendering** (Efficient memory usage and performance)
* **Escaped Braces Handling** with `'<` and `>'`
* **Full File Rendering with `render_text_by_path`** (Highly recommended)

---

## 🔧 Installation

Simply require the engine in your Lua project:

```lua
Candango = require("CandangoEngine.CandangoEngine")
```

---

## 🧠 Syntax Overview

### 1. **Variable Insertion** `{}`

Insert variables directly in your text:

```html
<h1>Hello, {variables["name"]}</h1>
```

---

### 2. **Raw Lua Execution** `#{}`

Execute Lua code without expecting a return:

```html
#{
    print("Executed inside the template!")
}
```

> Tip: If your code contains a closing brace `}` as part of a string or table, you can escape the section using `<` and `>` like this:

```lua
#{
    samuel = {'<}>'}
}
```

---

### 3. **Lua Execution with Return** `!{}`

Execute code blocks where the result must be rendered in the output:

```html
!{
    if variables.age >= 18 then
        return "<p>You are an adult.</p>"
    else
        return "<p>You are a minor.</p>"
    end
}
```

---

### 4. **Ignore Code Blocks** `$#` and `#$`

Wrap any section to be completely ignored (not parsed as Lua):

```html
$#
This is ignored even if it contains {or !{ or #{
#$
```

---

## 🔐 Escaping Braces

To avoid prematurely closing a brace with matching content, use the escape format `<` before and `>` after your brace:

```lua
!{
    local samuel = {'<}>'}
}
```

This ensures that the engine won't mistakenly close the block early.

---

## ⚙️ API Reference

### Recommended Usage:

```lua
local Candango = require("CandangoEngine.CandangoEngine")

local variables = {
    name = "sam",
    age = 14
}

local function main()
    local response = Candango.render_text_by_path("small_text.txt")

    if response.in_error then
        return response.error_message
    end

    return response.text
end

print(main())
```

---

## 📄 Example Template (small\_text.txt)

```html
Candango = require("CandangoEngine.CandangoEngine")

Keys.raw.init = "###{"

variables = {
  name="sam",
  age=14
}

local function main()

  local response = Candango.render_text_by_path("small_text.txt")

  print(response.in_error, "\n")

  if response.in_error then
    return response.error_message
  end

  return response.text
end

print(main())
if samuel then
  print(samuel.age)
end
```

### Output:

```
Funcionando perfeitamente!
false

lua main.lua
Funcionando perfeitamente!
false	

<html>
    <head>
        <title>My Dynamic Page</title>
    </head>
    <body>
        <h1>Welcome, sam</h1>
        <p>Age: 14</p>



        <p>You are a minor.</p>
    </body>
</html>

sam
```

---

## 📌 Performance Tip

Always prefer to use `render_text_by_path(path)` instead of passing large text directly. This function handles chunked file reading internally, ensuring optimized memory usage and faster rendering.

---

## 🛠️ Customizing Keys (Optional)

You can customize how the engine detects special blocks by modifying the `Keys` object:

```lua
Keys.raw.init = "###{"
Keys.raw.end = "}"
```

---

## 🧩 Integration

CandangoEngine is modular and can be integrated easily into any Lua-based project, making it an ideal choice for static site generation, dynamic report rendering, or even lightweight web frameworks.

---


