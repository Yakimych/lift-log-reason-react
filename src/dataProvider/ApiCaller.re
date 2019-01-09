[@bs.val] external apiBaseUrl: string = "process.env.REACT_APP_API_BASE_URL";

let liftLogsUrl = apiBaseUrl ++ "/LiftLogs/";

let getLiftLogUrl = logName => liftLogsUrl ++ logName;
let addEntryUrl = logName => getLiftLogUrl(logName) ++ "/lifts";

let fetchLiftLog = (logName, successAction, errorAction) => {
  Js.Promise.(
    Axios.get(logName |> getLiftLogUrl)
    |> then_(response =>
         response##data |> Decode.liftLog |> successAction |> resolve
       )
    |> catch(error => error |> errorAction |> resolve)
    |> ignore
  );
};

let toApiSet = (set: AppState.set) => {
  "numberOfReps": set.reps,
  "rpe": set.rpe,
};

let addLogEntry =
    (logName, logEntry: AppState.liftLogEntry, successAction, errorAction) => {
  let apiEntry = {
    "name": logEntry.name,
    "weightLifted": logEntry.weightLifted,
    "date": logEntry.date,
    "sets": logEntry.sets |> Array.of_list |> Array.map(toApiSet),
  };

  Js.log("Adding entry: ");
  Js.log(apiEntry);

  Js.Promise.
    /* Axios.postData(logName |> addEntryUrl, apiEntry) */
    (
      Axios.post(logName |> addEntryUrl)
      |> then_(response => response |> successAction |> resolve)
      |> catch(error => error |> errorAction |> resolve)
      |> ignore
    );
};
