
cmdtree
=======

![cmdtree](https://jb55.com/s/cmdtree.png)

cmdtree is a command launcher in the form of a trie. Commands are launched by a
sequence of keys that form a path in this trie.

Configuring cmdtree is easy (this format is still WIP):

`~/.cmdtreerc` or `~/.config/cmdtree/cmdtreerc`:

    (commands
     (a application
        (b chrome)
        (e emacs))
     (e email
        (f fetch-email)))
