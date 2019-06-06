open AppState;

[@react.component]
let make = (~entries: list(liftLogEntry)) => {
  <div className="lifts">
    {entries
     ->Belt.List.reverse
     ->Belt.List.mapWithIndex((index, logEntry) =>
         <LiftRow entry=logEntry key={string_of_int(index)} />
       )
     ->Belt.List.toArray
     |> ReasonReact.array}
  </div>;
};
