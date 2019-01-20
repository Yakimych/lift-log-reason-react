open Jest;
open Expect;
open Utils;
open AppState;

describe("Utils", () =>
  describe("toValidSet", () => {
    test("should return None for empty string", () =>
      expect(toValidSet("")) |> toBe(None)
    );

    test("should return None for invalid string", () =>
      expect(toValidSet("asd")) |> toBe(None)
    );

    test("should return correct reps value for a string without RPE", () =>
      expect(toValidSet("9")) |> toEqual(Some({reps: 9, rpe: None}))
    );

    test("should return correct reps and RPE values for a string with RPE", () =>
      expect(toValidSet("9@9.5"))
      |> toEqual(Some({reps: 9, rpe: Some(9.5)}))
    );

    test("should return only reps value for a string with too high RPE", () =>
      expect(toValidSet("9@10.5")) |> toEqual(Some({reps: 9, rpe: None}))
    );

    test("should return only reps value for a string with invalid RPE", () =>
      expect(toValidSet("9@10.sad")) |> toEqual(Some({reps: 9, rpe: None}))
    );
  })
);
