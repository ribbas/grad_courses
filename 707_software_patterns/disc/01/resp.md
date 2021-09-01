# Null Object

## 1

**Is NullObject suitable or preferable as a list terminator? Why or why not?
e.g., instead of the "NULL" in:**

```
for (Obj o = list.start(); o != NULL; o=o.next()) {}
```

Replacing the usage of NULL with the NullObject in the provided snippet above would implement something similar to the following:

```
for (Obj o = list.start(); !o.is_null_object(); o=o.next()) {}
```

where `Obj.is_null_object()` simply preforms an equality comparison to the type of the current object to its corresponding NullObject and returns the resulting boolean.

Although it may appear that the underlying implementation is simple (i.e. `o.is_null_object()` may simply wrap `o == NullObject`), that does not necessarily have to be the case. The NullObject class of the `Obj` class may be a standalone class or an inherited implementation where all of the base attributes are empty and methods are overridden to "do nothing". The additional `Obj.is_null_object()` method would have to compare the base class object to its corresponding NullObject. Comparing these objects will require the `Obj` class to support the comparison and return the expected behavior.

Since the expected behavior of the method would be to act as a list terminator, there would be a requirement for an additional NullObject implementation for a list that holds `Obj2` classes. In the case of the NullObject classes being standalone classes, it is possible to implement a single NullObject class that abstracts the base class comparisons with templated methods. In the case of the NullObject classes being inheritances, there would be an additional class implementation for every base class. Regardless of the method of implementation of the NullObject, this would introduce some code bloat especially for a class that is intended to "do nothing".

## 2

The pattern description states circumstances in which NullObject should be applied. What behaviors would not benefit from representation as a NullObject?

## 3

At what level in a type hierarchy is it appropriate to implement the NullObject behavior? i.e., does every interface related by inheritance need one?
