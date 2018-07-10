
cmdtree
=======

![cmdtree](https://jb55.com/s/cmdtree.png?)

![cmdtree2](https://jb55.com/s/cmdtree2.png?)

cmdtree is a command launcher in the form of a trie. Commands are launched by a
sequence of keys that form a path in this trie.

Configuring cmdtree will be easy (not yet implemented, still WIP):

`~/.cmdtreerc` or `~/.config/cmdtree/cmdtreerc`:

    (commands
     (a application
        (b chrome)
        (e emacs))
     (e email
        (f fetch-email)))

Configuring cmdtree currently requires you to edit a C header file, similar to
dmenu. You will need to tweak [cfg.def.h](cfg.def.h) to your liking before
building. This is temporary until the configuration file format is complete, but
it has the benefit of being quite fast to launch!

Installing
----------

First customize [cfg.def.h](cfg.def.h) to include your menu items.

libX11 and libXft are required. Once you have those installed, simply type:

    make && make install || sudo make install

To launch `cmdtree` with a key binding, use something like
[xbindkeys](https://wiki.archlinux.org/index.php/Xbindkeys)


Key Bindings
------------

```
ESC         quit
Backspace   go up one level
```
