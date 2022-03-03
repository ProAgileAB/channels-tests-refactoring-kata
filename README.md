# channels-tests-refactoring-kata

This is a refactoring kata that focuses on refactoring the test code rather than production code.

The idea is to improve the readability of the 'arrange' part of the tests in branch 'main', to use
the Test Data Builder pattern. The starting point already has some examples of the pattern, which
should give you inspiration to add more builders.

# Problems to work on

1. Begin by reading through builders.h and builder.c.
  * How many builder functions already exists? Count all functions.
  * What structs have at least one builder function?
  * Compare with the production structs in channel.h, which fields lack builders?
2. test_channel.c contains fixture based tests for the should_send_packet function (top half of file) and tests for builders (bottom half).
  * How many tests are fixture based?
  * How many tests are there for test data builder functions?
  * Place Arrange, Act, Assert comments in each of the should_send_packet tests (as best as you can)
3. Time for refactoring!
  * There are several TODO items in test_channel.c
  * Some are marked EASY and HARD - start with an EASY!

# Links

This kata is sponsored by [ProAgile](https://proagile.se).
