(:*******************************************************:)
(: Test: K2-SeqDocFunc-3                                 :)
(: Written by: Frans Englich                             :)
(: Date: 2007-11-22T11:31:21+01:00                       :)
(: Purpose: Load an unexisting file via the file:// protocol. :)
(:*******************************************************:)
fn:doc(xs:untypedAtomic("file:///example.com/does/not/exist/xqts-testing.xml"))