open AppState;

[@react.component]
let make = (~entry: liftLogEntry) => {
  <div className="row">
    <span className="col">
      {entry.date |> Utils.toCustomDateFormat |> ReasonReact.string}
    </span>
    <span className="col"> {entry.name |> ReasonReact.string} </span>
    <span className="col">
      {entry.weightLifted |> Js.Float.toString |> ReasonReact.string}
    </span>
    <span className="col">
      {entry.sets |> Utils.formatSets |> ReasonReact.string}
    </span>
  </div>;
};
