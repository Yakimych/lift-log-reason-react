open AppState;

let set = json => {
  open! Json.Decode;
  {
    reps: json |> field("numberOfReps", int),
    rpe: json |> field("rpe", optional(float)),
  };
};

let logEntry = json => {
  open! Json.Decode;
  {
    name: json |> field("name", string),
    weightLifted: json |> field("weightLifted", float),
    date: json |> field("date", date),
    sets: json |> field("sets", list(set)),
  };
};

let liftLog = json =>
  Json.Decode.{
    name: json |> field("name", string),
    title: json |> field("title", string),
    entries: json |> field("entries", list(logEntry)),
  };
