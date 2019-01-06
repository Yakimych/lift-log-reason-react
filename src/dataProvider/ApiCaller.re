[@bs.val] external apiBaseUrl: string = "process.env.REACT_APP_API_BASE_URL";

let liftLogsUrl = apiBaseUrl ++ "/LiftLogs/";

let getLiftLogUrl = logName => liftLogsUrl ++ logName;

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
