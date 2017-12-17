open Jest;

describe("test", () =>
  Expect.(
    test("toBe", () => {
      let tests = ["1122", "1111", "1234", "91212129"];
      let expected = [3, 4, 0, 9];
      let actual = List.map(Day1.processInput, tests);
      expect(expected) |> toBe(actual);
    })
  )
);