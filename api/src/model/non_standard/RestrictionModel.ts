export const BEEF = "beef";
export const CHICKEN = "chicken";
export const FISH = "fish";
export const SHELLFISH = "shellfish";
export const DAIRY = "dairy";
export const EGGS = "eggs";
export const GLUTEN = "gluten";
export const PEANUTS = "peanuts";
export const NUTS = "nuts";
export const SOY = "soy";

export enum TypeId {
  BEEF = "beef",
  CHICKEN = "chicken",
  FISH = "fish",
  SHELLFISH = "shellfish",
  DAIRY = "dairy",
  EGGS = "eggs",
  GLUTEN = "gluten",
  PEANUTS = "peanuts",
  NUTS = "nuts",
  SOY = "soy",
};

export const all = [
  TypeId.BEEF,
  TypeId.CHICKEN,
  TypeId.FISH,
  TypeId.SHELLFISH,
  TypeId.DAIRY,
  TypeId.EGGS,
  TypeId.GLUTEN,
  TypeId.PEANUTS,
  TypeId.NUTS,
  TypeId.SOY,
];

type modelType = {
  image: string
};

type databaseObject = {
  [key in TypeId]: modelType
};

export const DATABASE_OBJECT : databaseObject = {
  [BEEF]: {
    image: '/icons/food/beef.gif',
  },
  [CHICKEN]: {
    image: '/icons/food/chicken.gif',
  },
  [FISH]: {
    image: '/icons/food/fish.gif',
  },
  [SHELLFISH]: {
    image: '/icons/food/shellfish.gif',
  },
  [DAIRY]: {
    image: '/icons/food/dairy.gif',
  },
  [EGGS]: {
    image: '/icons/food/eggs.gif',
  },
  [GLUTEN]: {
    image: '/icons/food/gluten.gif',
  },
  [PEANUTS]: {
    image: '/icons/food/peanuts.gif',
  },
  [NUTS]: {
    image: '/icons/food/nuts.gif',
  },
  [SOY]: {
    image: '/icons/food/soy.gif',
  },
};