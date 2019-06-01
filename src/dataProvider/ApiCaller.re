[@bs.val] external apiBaseUrl: string = "process.env.REACT_APP_API_BASE_URL";

let liftLogsUrl = apiBaseUrl ++ "/LiftLogs/";

let getLiftLogUrl = logName => liftLogsUrl ++ logName;
let addEntryUrl = logName => getLiftLogUrl(logName) ++ "/lifts";

let fetchLiftLog = logName => {
  Js.Promise.(
    Axios.get(logName |> getLiftLogUrl)
    |> then_(response => response##data |> Decode.liftLog |> resolve)
  );
};

let toApiSet = (set: AppState.set) => {
  "numberOfReps": set.reps,
  "rpe": set.rpe,
};

let toApiLink = (link: AppState.liftInfoLink) => {
  "text": link.text,
  "url": link.url,
};

let addLogEntry = (logName, logEntry: AppState.liftLogEntry) => {
  let apiEntry = {
    "name": logEntry.name,
    "weightLifted": logEntry.weightLifted,
    "date": logEntry.date,
    "sets": logEntry.sets |> Array.of_list |> Array.map(toApiSet),
    "comment": logEntry.comment,
    "links": logEntry.links |> Array.of_list |> Array.map(toApiLink),
  };

  // TODO: Remove
  Js.log("Adding entry: ");
  Js.log(apiEntry);

  Axios.postData(logName |> addEntryUrl, apiEntry);
};
