
let acc($m,$n)={
  if $n == 0 then $m else acc($m+$n, $n-1);
}

begin:
  var a = acc(0,5);
  print(a);
end;