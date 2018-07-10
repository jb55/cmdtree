
cmdtree
=======

![cmdtree](https://jb55.com/s/cmdtree.png)

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

Configuring cmdtree is currently not so easy, but you just need to tweak
[cfg.def.h](cfg.def.h) to your liking before building.
