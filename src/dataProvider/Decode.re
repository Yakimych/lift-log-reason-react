open AppState;

let set = json => {
  open! Json.Decode;
  {
    reps: json |> field("numberOfReps", int),
    rpe: json |> field("rpe", optional(float)),
  };
};

let link = json => {
  open! Json.Decode;
  {text: json |> field("text", string), url: json |> field("url", string)};
};

let logEntry = json => {
  open! Json.Decode;
  {
    name: json |> field("name", string),
    weightLifted: json |> field("weightLifted", float),
    date: json |> field("date", date),
    sets: json |> field("sets", list(set)),
    comment:
      (json |> optional(field("comment", string)))
      ->Belt.Option.getWithDefault(""),
    links:
      (json |> optional(field("links", list(link))))
      ->Belt.Option.getWithDefault([]),
  };
};

let liftLog = json =>
  Json.Decode.{
    name: json |> field("name", string),
    title: json |> field("title", string),
    entries: json |> field("entries", list(logEntry)),
  };
