open AppState;

[@react.component]
let make = (~entries: list(liftLogEntry)) => {
  <>
    <div className="row">
      <h6 className="col"> {"Date" |> ReasonReact.string} </h6>
      <h6 className="col"> {"Name" |> ReasonReact.string} </h6>
      <h6 className="col"> {"Weight lifted (kg)" |> ReasonReact.string} </h6>
      <h6 className="col"> {"Sets/Reps" |> ReasonReact.string} </h6>
    </div>
    <div className="lifts">
      {entries
       |> List.rev
       |> List.mapi((index, logEntry) =>
            <LiftRow entry=logEntry key={string_of_int(index)} />
          )
       |> Array.of_list
       |> ReasonReact.array}
    </div>
  </>;
};
