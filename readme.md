# a newt binding library for Lua 5.3

This is a simple [newt][newt] binding library for lua 5.3, fork from [luanewt][luanewt].

It has been tested only on Mac OS X and Centos 6.

## TODO

* complete the empty binding function
* improve the Lua api
* add documentation with [LDoc][LDoc]

## build & usage

install deps

```zsh
brew install newt # MacOS X
yum install -y newt-devel # CentOS
```

and then just do `make`, run test with `make test`

[newt]: https://en.wikipedia.org/wiki/Newt_(programming_library)
[luanewt]: https://github.com/SnarkyClark/luanewt
[LDoc]: https://github.com/stevedonovan/LDoc
