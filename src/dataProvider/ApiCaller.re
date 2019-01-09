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

let addLogEntry = (logName, logEntry, successAction, errorAction) => {
  /* TODO: Add body */
  Js.log(logEntry);
  Js.Promise.(
    Axios.post(logName |> addEntryUrl)
    |> then_(response => response |> successAction |> resolve)
    |> catch(error => error |> errorAction |> resolve)
    |> ignore
  );
};
