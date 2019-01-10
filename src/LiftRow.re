open AppState;

let component = ReasonReact.statelessComponent("LiftRow");

let make = (~entry: liftLogEntry, _children) => {
  ...component,
  render: _self =>
    <div className="row">
      <span className="col">
        {entry.date |> Js.Date.toLocaleDateString |> ReasonReact.string}
      </span>
      <span className="col"> {entry.name |> ReasonReact.string} </span>
      <span className="col">
        {entry.weightLifted |> string_of_float |> ReasonReact.string}
      </span>
      <span className="col">
        {entry.sets |> Utils.formatSets |> ReasonReact.string}
      </span>
    </div>,
};
