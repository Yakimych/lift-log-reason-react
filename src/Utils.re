let removeAtIndex = (index, list) =>
  list
  |> List.mapi((i, x) => (i, x))
  |> List.filter(t => t |> fst != index)
  |> List.map(t => t |> snd);

let changeAtIndex = (index, replaceFunc, newValue, list) =>
  list
  |> List.mapi((i, x) => (i, x))
  |> List.map(t =>
       if (t |> fst == index) {
         t |> snd |> replaceFunc(newValue);
       } else {
         t |> snd;
       }
     );

let replaceFunc = (newValue, _) => newValue;
