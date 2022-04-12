# channels-tests-refactoring-kata

This is a refactoring kata that focuses on refactoring the Arrange part of test code, rather than
production code. Test code needs <3 too to be kept maintainable, readable and grokkable. And test
data builder pattern may be something you can apply when you see hard-to-understand Arrange sections
of tests, or large fixtures.

The idea is to improve the readability of the 'arrange' part of the tests in branch 'main', to use
the Test Data Builder pattern. The starting point already has some examples of the pattern, which
should give you inspiration to add more builders.

# Domain

We are improving the already existing tests of a function called `should_send_packet()`.

`should_send_packet()` is defined in `channel.c`, but is not the focus of this exercise - it is just a dummy
to have something to test against.

# Exercises

1. test_channel.c contains fixture based tests for the `should_send_packet` function (top half of file) and tests for builders (bottom half).
  * How many tests are fixture based?
    * Answer:
  * How many tests are test data builder based?
    * Answer:
  * Add Arrange, Act, Assert comments in each of the should_send_packet tests (as best as you can)
2. Read through `builders.h` and `builder.c`.
  * How many builder functions already exists? Count all functions in `builders.h`.
    * Answer:
  * What are the names of the structs that have at least one builder function?
    * Answer:
  * Compare with the production structs in `channel.h`, which fields lack builders?
    * Answer:
3. Time for refactoring!
  * There are several TODO items in test_channel.c
  * Some are marked EASY and HARD - start with an EASY!

# Links

This kata is sponsored by [ProAgile](https://proagile.se).
