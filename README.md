nnif1
=====

This is my neural network interconnect.  I am not sure, but I believe I invented (if not, reinvented) this function.  Proof will be found in the form of that someone with a math background could have done a much better job.

I created this function for the Netflix Prize competition.  I don't have an actual date, but my gut feeling was it was three months or so after the contest began, which places it around January 2007ish.



StoneCypher's Neural Net Interconnect Function 1
------------------------------------------------

It turns out that you can get some seriously funky shape effects by
pissing around with coefficients in the canonical fast sigmoid

```
              x
    f(x) = -------
           1 + |x|
```

Now, first we start by expanding that for shifting behavior

```
                       x+ho
    f(x, ho, vo) = ---------- + vo
                   1 + |x+ho|
```

However, if we give different horizontal offsets to the numerator and
denominator, suddenly we get a curve compression at the curve middle
which I am absolutely not going to try to ascii art.

```
                          x+h1
    f(x, h1, h2, vo) = ---------- + vo
                       1 + |x+h2|
```

This should allow the network to create a stronger bias against one
kind of wrongness than the other at its discretion, and to as much as
eliminate the penalty for one side of wrongness - something that may
be an important discriminatory tool.

More amusing still, with sign inversion, you can get a "seagull wing"
effect (vertically invertible) with no asymptote at no apparent extra
cost.

Furthermore, the steepness of the gradient can be controlled by taking
over the denominator addend:

```
                             x+h1
    f(x, h1, h2, vo, s) = ---------- + vo
                          s + |x+h2|
```

With a negative S in sigmoid parameters, this creates a bizarre
double-hyperbolic shape; with a negative S in "gull" parameters,
it creates the same double-hyperbolic but with one side inverted,
in the middle creating a reasonable approximation of a bell (easily
imitating a bell by bounding.)  This effect is biassable by
*multiplying* the numerator.  However, more entertaining still, if
you divide the numerator, you get the double hyperbola with a
decreasing range (not unlike a heartbeat).  Calling that nc (the
numerator coefficient,) and using multiplying by an inverse to
effect division, we get

```
                              (x*nc)+h1
    f(x, nc, h1, h2, vo, s) = ---------- + vo
                              s + |x+h2|
```

To finish it off, we add vertical scaling:

```
                                    / (x*nc)+h1      \
    f(x, xs, nc, h1, h2, vo, s) =  ( ----------- * xs ) + vo
                                    \ s + |x+h2|     /
```

This, dear friends, is a /remarkably/ flexible function.  Throw in
a branch to prevent divide by zero, and we have teh winnar.

This is implemented as a template function, in order to be valid
for any type supporting at least: `==` `<` `+` `unary-` `*` `/`

This code prevents divide by zero.
