open AppState;

let component = ReasonReact.statelessComponent("LiftRow");

let make = (~entry: liftLogEntry, _children) => {
  ...component,
  render: _self =>
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
    </div>,
};
