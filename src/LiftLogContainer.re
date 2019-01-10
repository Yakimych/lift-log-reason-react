open AppState;

let component = ReasonReact.statelessComponent("LiftContainer");

let make = (~entries: list(liftLogEntry), _children) => {
  ...component,
  render: _self => {
    <>
      <div className="mt-3 mb-3 p-2 box-shadow lift-log-container">
        <div className="row">
          <h6 className="col"> {"Date" |> ReasonReact.string} </h6>
          <h6 className="col"> {"Name" |> ReasonReact.string} </h6>
          <h6 className="col">
            {"Weight lifted (kg)" |> ReasonReact.string}
          </h6>
          <h6 className="col"> {"Sets/Reps" |> ReasonReact.string} </h6>
        </div>
      </div>
      <div className="lifts">
        {entries
         |> List.mapi((index, logEntry) =>
              <LiftRow entry=logEntry key={string_of_int(index)} />
            )
         |> Array.of_list
         |> ReasonReact.array}
      </div>
    </>;
  },
};
