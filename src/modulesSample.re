/*
    Modules:
 */
/*
  ## Modul-Dateien:
   - Per default stellt in Reason jede Quellcode-Datei
   ein Modul dar (Modul-Dateien)
   - Per default werden alle top-level Variablen in einer
   Modul-Datei exportiert.
   - Modul-Dateien werden normalerweise kleingeschrieben,
   CamelCase (meinModule.re)
   - Der Modul-Name einer Modul-Dateien entspricht dem
   Datei-Namen (aber großgeschrieben).
 */
/*
 ## Unter-Module in einer Modul-Datei:
 module MeinModul = { ... }
  */
module Zoo = {
  type animal = {
    name: string,
    species: string
  };
  let animals = ref(Hashtbl.create(0): Hashtbl.t(string, string));
  let addAnimal = animal => Hashtbl.add(animals^, animal.name, animal.species);
  let visitAnimals: (animal => unit) => unit =
    f => animals^ |> Hashtbl.iter((name, species) => f({name, species}));
  let zooName = "Zur Schlangengrube";
  let description = "Kaninchen Stall mit angeschlossenem Terrarium";
};

/* Add some animals to the zoo */
[
  ("Max", "Meerschweinchen"),
  ("Josef", "Kaninchen"),
  ("Maxine", "Maus"),
  ("Klara", "Schlange")
]
|> List.iter(((name, species))
     /* Call Module function: */
     => Zoo.addAnimal({name, species}));

/* Call Module function: */
Zoo.visitAnimals(({name, species}) =>
  Js.log({j|name: $name von Spezies: $species|j})
);

/*
  ## Importieren:
  - Module werden über ihren Modul-Namen referenziert.
  - Ein Modul kann auch nur für eine Expressions referenziert
  werden: MyModule.(....)
  - Ein Modul kann auch für eine ganze Modul-Datei importiert werden:
  open MyModule;
 */
Js.log(Zoo.zooName);

Zoo.(Js.log({j|ZooName: $zooName und Description: $description|j}));

open Zoo;

Js.log({j|ZooName: $zooName und Description: $description|j});
/* Signatur eines Modules: Module-Interface */
/* https://reasonml.github.io/guide/language/module/ */