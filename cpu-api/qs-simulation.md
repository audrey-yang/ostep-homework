# Homework

1. > Run ./fork.py -s 10 and see which actions are taken.

   I predict that it will look as follows:

   ```
   Action: a forks b
   a
   └── b
   Action: a forks c
   a
   └── b
   └── c
   Action: c EXITS
   a
   └── b
   Action: a forks d
   a
   └── b
   └── d
   Action: a forks e
   a
   └── b
   └── d
   └── e
   ```

2. > Run the simulator with a large number of actions (e.g., -a 100) and vary the fork_percentage from 0.1 to 0.9. What do you think the resulting final process trees will look like as the percentage changes?

   When the fork percentage is high, I'd expect the tree to look fuller, with almost all processes still in it. When it is low, I'd expect the final tree to be sparser, with not as many processes remaining.

   ```
   a = 100, fork_percentage = 0.1

   a
    ├── Z
    └── Y

   a = 100, fork_percentage = 0.5

   a
    ├── x
    ├── D
    ├── E
    │   ├── R
    │   ├── ac
    │   │   └── ad
    │   └── af
    ├── K
    │   ├── ab
    │   └── ag
    ├── N
    ├── P
    │   └── Y
    │       └── ae
    ├── S
    └── aa


   a = 100, fork_percentage = 0.9

   a
    ├── b
    │   ├── d
    │   │   ├── o
    │   │   │   └── y
    │   │   │       ├── E
    │   │   │       │   └── al
    │   │   │       ├── H
    │   │   │       │   └── aL
    │   │   │       ├── R
    │   │   │       │   └── ab
    │   │   │       └── V
    │   │   │           └── aP
    │   │   ├── s
    │   │   │   ├── W
    │   │   │   └── ak
    │   │   └── ai
    │   │       └── ap
    │   └── aR
    ├── c
    │   ├── g
    │   │   ├── n
    │   │   │   ├── u
    │   │   │   │   ├── K
    │   │   │   │   │   ├── M
    │   │   │   │   │   │   └── ah
    │   │   │   │   │   └── aE
    │   │   │   │   │       └── aQ
    │   │   │   │   └── S
    │   │   │   │       └── ac
    │   │   │   ├── w
    │   │   │   ├── D
    │   │   │   ├── F
    │   │   │   └── ao
    │   │   ├── t
    │   │   │   ├── x
    │   │   │   │   └── O
    │   │   │   │       └── ax
    │   │   │   ├── C
    │   │   │   ├── N
    │   │   │   │   └── T
    │   │   │   └── aN
    │   │   ├── z
    │   │   │   └── Y
    │   │   │       ├── ay
    │   │   │       │   └── aD
    │   │   │       │       └── aH
    │   │   │       └── aA
    │   │   └── I
    │   │       ├── J
    │   │       ├── P
    │   │       │   └── av
    │   │       └── aj
    │   │           ├── aM
    │   │           └── aO
    │   ├── m
    │   │   └── Z
    │   │       └── au
    │   │           └── aw
    │   └── aG
    │       └── aJ
    ├── f
    │   ├── i
    │   │   └── L
    │   ├── k
    │   │   └── U
    │   │       ├── ad
    │   │       ├── az
    │   │       └── aK
    │   ├── l
    │   │   └── A
    │   │       └── aB
    │   └── ae
    ├── h
    │   └── p
    │       ├── B
    │       │   └── an
    │       ├── ag
    │       ├── aq
    │       │   └── aC
    │       └── aI
    ├── r
    ├── G
    │   ├── Q
    │   ├── X
    │   ├── aa
    │   │   └── at
    │   └── am
    ├── af
    │   └── ar
    └── aF
   ```

3. > Now, switch the output by using the -tflag (e.g., run ./fork.py -t). Given a set of process trees, can you tell which actions were taken?

   ```
                              Process Tree:
                               a

    a forks b
                                a
                                └── b
    b forks c
                                a
                                └── b
                                    └── c
    c EXITS
                                a
                                └── b
    a forks d
                                a
                                ├── b
                                └── d
    d forks e
                                a
                                ├── b
                                └── d
                                    └── e
   ```

4. > T o study this, let’s create a specific example: `./fork.py -A a+b,b+c,c+d,c+e,c-`. This example has process ’a’ create ’b’, which in turn creates ’c’, which then creates ’d’ and ’e’. However, then, ’c’ exits. What do you think the process tree should like after the exit? What if you use the -R flag?

   After the exit of c, we might see d and e get claimed by intial process a. We also might see them disappear, as they would be cleaned up by process a.

   The -R flag seems to be to toggle "local_reparent." In this case, we'd expect d and e to move up as children of b.

   ```
   without -R
                              Process Tree:
                               a

    Action: a forks b
                                a
                                └── b
    Action: b forks c
                                a
                                └── b
                                    └── c
    Action: c forks d
                                a
                                └── b
                                    └── c
                                        └── d
    Action: c forks e
                                a
                                └── b
                                    └── c
                                        ├── d
                                        └── e
    Action: c EXITS
                                a
                                ├── b
                                ├── d
                                └── e

   with -R

                            Process Tree:
                               a

    Action: a forks b
                                a
                                └── b
    Action: b forks c
                                a
                                └── b
                                    └── c
    Action: c forks d
                                a
                                └── b
                                    └── c
                                        └── d
    Action: c forks e
                                a
                                └── b
                                    └── c
                                        ├── d
                                        └── e
    Action: c EXITS
                                a
                                └── b
                                    ├── d
                                    └── e
   ```

5. > Run ./fork.py -F and see if you can write down the final tree by looking at the series of actions generated.

   ```
   -s 2

   Action: a forks b
   Action: b EXITS
   Action: a forks c
   Action: c forks d
   Action: a forks e

                                a
                                └── c
                                │   └── d
                                └── e

   -s 11

   Action: a forks b
   Action: b forks c
   Action: b forks d
   Action: d forks e
   Action: b forks f

                                a
                                └── b
                                    └── c
                                    └── d
                                    │   └── e
                                    └── f
   ```

6. > Finally, use both -t and -F together. By looking at the tree, can you determine the exact actions that took place? In which cases can you tell? In which can’t you tell?

   ```
   -s 24

   Action: a forks b
   Action: b forks c
   Action: c forks d
   Action: d EXITS
   Action: c forks e

                        Final Process Tree:
                               a
                               └── b
                                   └── c
                                       └── e

   -s 999

   Action: a forks b
   Action: b EXITS
   Action: a forks c
   Action: a forks d
   Action: d forks e

                        Final Process Tree:
                               a
                               ├── c
                               └── d
                                   └── e
   ```

   In some of these scenarios, the order of operations may be ambiguous. It becomes even less clear when many of the processes have exited. For example, I ran `./fork.py -s 9009429 -t -F -a 100 -f 0.1` and the same tree for my starting and ending states. In this case, there is really no way to tell what happened.

   ```
                        Process Tree:
                               a
   ```
