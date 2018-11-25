import * as Restriction from './RestrictionModel';

export enum TypeId {
  OMNIVORE = "omnivore",
  VEGETARIAN = "vegetarian",
  VEGAN = "vegan",
  PESCATARIAN = "pescatarian",
  PALEO = "paleo",
};

export const all = [
  TypeId.OMNIVORE,
  TypeId.VEGETARIAN,
  TypeId.VEGAN,
  TypeId.PESCATARIAN,
  TypeId.PALEO
];

type modelType = {
  restrictions: Restriction.TypeId[]
}

type databaseObject = {
  [key in TypeId]: modelType
};

export const DATABASE_OBJECT : databaseObject = {
  [TypeId.OMNIVORE]: {
    restrictions: []
  },
  [TypeId.VEGETARIAN]: {
    restrictions: [
      Restriction.TypeId.BEEF,
      Restriction.TypeId.CHICKEN,
      Restriction.TypeId.FISH,
      Restriction.TypeId.SHELLFISH,
    ]
  },
  [TypeId.VEGAN]: {
    restrictions: [
      Restriction.TypeId.BEEF,
      Restriction.TypeId.CHICKEN,
      Restriction.TypeId.FISH,
      Restriction.TypeId.SHELLFISH,
      Restriction.TypeId.DAIRY,
      Restriction.TypeId.EGGS,
    ]
  },
  [TypeId.PESCATARIAN]: {
    restrictions: [
      Restriction.TypeId.BEEF,
      Restriction.TypeId.CHICKEN,
    ]
  },
  [TypeId.PALEO]: {
    restrictions: [
      Restriction.TypeId.DAIRY,
      Restriction.TypeId.GLUTEN,
      Restriction.TypeId.PEANUTS,
      Restriction.TypeId.SOY,
    ]
  },
};