#include <string>

std::string middleclass = ""
                          "local middleclass = {\n"
                          "  _VERSION     = 'middleclass v4.1.0',\n"
                          "  _DESCRIPTION = 'Object Orientation for Lua',\n"
                          "  _URL         = 'https://github.com/kikito/middleclass',\n"
                          "  _LICENSE     = [[\n"
                          "    MIT LICENSE\n"
                          "\n"
                          "    Copyright (c) 2011 Enrique Garc?a Cota\n"
                          "\n"
                          "    Permission is hereby granted, free of charge, to any person obtaining a\n"
                          "    copy of this software and associated documentation files (the\n"
                          "    \"Software\"), to deal in the Software without restriction, including\n"
                          "    without limitation the rights to use, copy, modify, merge, publish,\n"
                          "    distribute, sublicense, and/or sell copies of the Software, and to\n"
                          "    permit persons to whom the Software is furnished to do so, subject to\n"
                          "    the following conditions:\n"
                          "\n"
                          "    The above copyright notice and this permission notice shall be included\n"
                          "    in all copies or substantial portions of the Software.\n"
                          "\n"
                          "    THE SOFTWARE IS PROVIDED \"AS IS\", WITHOUT WARRANTY OF ANY KIND, EXPRESS\n"
                          "    OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF\n"
                          "    MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.\n"
                          "    IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY\n"
                          "    CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,\n"
                          "    TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE\n"
                          "    SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.\n"
                          "  ]]\n"
                          "}\n"
                          "\n"
                          "local function _createIndexWrapper(aClass, f)\n"
                          "  if f == nil then\n"
                          "    return aClass.__instanceDict\n"
                          "  else\n"
                          "    return function(self, name)\n"
                          "      local value = aClass.__instanceDict[name]\n"
                          "\n"
                          "      if value ~= nil then\n"
                          "        return value\n"
                          "      elseif type(f) == \"function\" then\n"
                          "        return (f(self, name))\n"
                          "      else\n"
                          "        return f[name]\n"
                          "      end\n"
                          "    end\n"
                          "  end\n"
                          "end\n"
                          "\n"
                          "local function _propagateInstanceMethod(aClass, name, f)\n"
                          "  f = name == \"__index\" and _createIndexWrapper(aClass, f) or f\n"
                          "  aClass.__instanceDict[name] = f\n"
                          "\n"
                          "  for subclass in pairs(aClass.subclasses) do\n"
                          "    if rawget(subclass.__declaredMethods, name) == nil then\n"
                          "      _propagateInstanceMethod(subclass, name, f)\n"
                          "    end\n"
                          "  end\n"
                          "end\n"
                          "\n"
                          "local function _declareInstanceMethod(aClass, name, f)\n"
                          "  aClass.__declaredMethods[name] = f\n"
                          "\n"
                          "  if f == nil and aClass.super then\n"
                          "    f = aClass.super.__instanceDict[name]\n"
                          "  end\n"
                          "\n"
                          "  _propagateInstanceMethod(aClass, name, f)\n"
                          "end\n"
                          "\n"
                          "local function _tostring(self) return \"class \" .. self.name end\n"
                          "local function _call(self, ...) return self:new(...) end\n"
                          "\n"
                          "local function _createClass(name, super)\n"
                          "  local dict = {}\n"
                          "  dict.__index = dict\n"
                          "\n"
                          "  local aClass = { name = name, super = super, static = {},\n"
                          "                   __instanceDict = dict, __declaredMethods = {},\n"
                          "                   subclasses = setmetatable({}, {__mode='k'})  }\n"
                          "\n"
                          "  if super then\n"
                          "    setmetatable(aClass.static, { __index = function(_,k) return rawget(dict,k) or super.static[k] end })\n"
                          "  else\n"
                          "    setmetatable(aClass.static, { __index = function(_,k) return rawget(dict,k) end })\n"
                          "  end\n"
                          "\n"
                          "  setmetatable(aClass, { __index = aClass.static, __tostring = _tostring,\n"
                          "                         __call = _call, __newindex = _declareInstanceMethod })\n"
                          "\n"
                          "  return aClass\n"
                          "end\n"
                          "\n"
                          "local function _includeMixin(aClass, mixin)\n"
                          "  assert(type(mixin) == 'table', \"mixin must be a table\")\n"
                          "\n"
                          "  for name,method in pairs(mixin) do\n"
                          "    if name ~= \"included\" and name ~= \"static\" then aClass[name] = method end\n"
                          "  end\n"
                          "\n"
                          "  for name,method in pairs(mixin.static or {}) do\n"
                          "    aClass.static[name] = method\n"
                          "  end\n"
                          "\n"
                          "  if type(mixin.included)==\"function\" then mixin:included(aClass) end\n"
                          "  return aClass\n"
                          "end\n"
                          "\n"
                          "local DefaultMixin = {\n"
                          "  __tostring   = function(self) return \"instance of \" .. tostring(self.class) end,\n"
                          "\n"
                          "  initialize   = function(self, ...) end,\n"
                          "\n"
                          "  isInstanceOf = function(self, aClass)\n"
                          "    return type(aClass) == 'table' and (aClass == self.class or self.class:isSubclassOf(aClass))\n"
                          "  end,\n"
                          "\n"
                          "  static = {\n"
                          "    allocate = function(self)\n"
                          "      assert(type(self) == 'table', \"Make sure that you are using 'Class:allocate' instead of 'Class.allocate'\")\n"
                          "      return setmetatable({ class = self }, self.__instanceDict)\n"
                          "    end,\n"
                          "\n"
                          "    new = function(self, ...)\n"
                          "      assert(type(self) == 'table', \"Make sure that you are using 'Class:new' instead of 'Class.new'\")\n"
                          "      local instance = self:allocate()\n"
                          "      instance:initialize(...)\n"
                          "      return instance\n"
                          "    end,\n"
                          "\n"
                          "    subclass = function(self, name)\n"
                          "      assert(type(self) == 'table', \"Make sure that you are using 'Class:subclass' instead of 'Class.subclass'\")\n"
                          "      assert(type(name) == \"string\", \"You must provide a name(string) for your class\")\n"
                          "\n"
                          "      local subclass = _createClass(name, self)\n"
                          "\n"
                          "      for methodName, f in pairs(self.__instanceDict) do\n"
                          "        _propagateInstanceMethod(subclass, methodName, f)\n"
                          "      end\n"
                          "      subclass.initialize = function(instance, ...) return self.initialize(instance, ...) end\n"
                          "\n"
                          "      self.subclasses[subclass] = true\n"
                          "      self:subclassed(subclass)\n"
                          "\n"
                          "      return subclass\n"
                          "    end,\n"
                          "\n"
                          "    subclassed = function(self, other) end,\n"
                          "\n"
                          "    isSubclassOf = function(self, other)\n"
                          "      return type(other)      == 'table' and\n"
                          "             type(self.super) == 'table' and\n"
                          "             ( self.super == other or self.super:isSubclassOf(other) )\n"
                          "    end,\n"
                          "\n"
                          "    include = function(self, ...)\n"
                          "      assert(type(self) == 'table', \"Make sure you that you are using 'Class:include' instead of 'Class.include'\")\n"
                          "      for _,mixin in ipairs({...}) do _includeMixin(self, mixin) end\n"
                          "      return self\n"
                          "    end\n"
                          "  }\n"
                          "}\n"
                          "\n"
                          "function middleclass.class(name, super)\n"
                          "  assert(type(name) == 'string', \"A name (string) is needed for the new class\")\n"
                          "  return super and super:subclass(name) or _includeMixin(_createClass(name), DefaultMixin)\n"
                          "end\n"
                          "\n"
                          "setmetatable(middleclass, { __call = function(_, ...) return middleclass.class(...) end })\n"
                          "\n"
                          "class = middleclass";
