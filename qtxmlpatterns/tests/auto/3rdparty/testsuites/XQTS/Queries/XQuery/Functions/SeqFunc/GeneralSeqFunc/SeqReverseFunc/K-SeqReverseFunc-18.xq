(:*******************************************************:)
(: Test: K-SeqReverseFunc-18                             :)
(: Written by: Frans Englich                             :)
(: Date: 2007-11-22T11:31:23+01:00                       :)
(: Purpose: Apply a predicate to the result of fn:reverse(). :)
(:*******************************************************:)
reverse((1, 2, 3))[last() - 1]