let apiBaseUrl = "http://localhost:5000/api/LiftLogs/";

let getLiftLogUrl = logName => apiBaseUrl ++ logName;

let fetchLiftLog = (logName, successAction, errorAction) => {
  Js.Promise.(
    Axios.get(logName |> getLiftLogUrl)
    |> then_(response =>
         response##data |> Decode.liftLog |> successAction |> resolve
       )
    |> catch(_ => errorAction |> resolve)
    |> ignore
  );
};
