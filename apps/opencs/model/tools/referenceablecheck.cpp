#include "referenceablecheck.hpp"

#include <sstream>
#include <map>
#include <cassert>

#include "../world/record.hpp"

#include "../world/universalid.hpp"

CSMTools::ReferenceableCheckStage::ReferenceableCheckStage(const CSMWorld::RefIdData& referenceable) :
    mReferencables(referenceable),
    mBooksSize(0),
    mActivatorsSize(0),
    mPotionsSize(0),
    mApparatiSize(0),
    mArmorsSzie(0),
    mClothingSize(0),
    mContainersSize(0),
    mCreaturesSize(0),
    mDoorsSize(0),
    mIngredientsSize(0),
    mCreaturesLevListsSize(0)
{
    setSizeVariables();
}

void CSMTools::ReferenceableCheckStage::setSizeVariables()
{
    mBooksSize = mReferencables.getBooks().getSize();
    mActivatorsSize = mReferencables.getActivators().getSize();
    mPotionsSize = mReferencables.getPotions().getSize();
    mApparatiSize = mReferencables.getApparati().getSize();
    mArmorsSzie = mReferencables.getArmors().getSize();
    mClothingSize = mReferencables.getClothing().getSize();
    mContainersSize = mReferencables.getContainers().getSize();
    mCreaturesSize = mReferencables.getCreatures().getSize();
    mDoorsSize = mReferencables.getDoors().getSize();
    mIngredientsSize = mReferencables.getIngredients().getSize();
    mCreaturesLevListsSize = mReferencables.getCreatureLevelledLists().getSize();
}

void CSMTools::ReferenceableCheckStage::perform(int stage, std::vector< std::string >& messages)
{
    //Checks for books, than, when stage is above mBooksSize goes to other checks, with (stage - PrevSum) as stage.
    if (stage < mBooksSize)
    {
        bookCheck(stage, mReferencables.getBooks(), messages);
        return;
    }

    stage -= mBooksSize;

    if (stage < mActivatorsSize)
    {
        activatorCheck(stage, mReferencables.getActivators(), messages);
        return;
    }

    stage -= mActivatorsSize;

    if (stage < mPotionsSize)
    {
        potionCheck(stage, mReferencables.getPotions(), messages);
        return;
    }

    stage -= mPotionsSize;

    if (stage < mApparatiSize)
    {
        apparatusCheck(stage, mReferencables.getApparati(), messages);
        return;
    }

    stage -= mApparatiSize;

    if (stage < mArmorsSzie)
    {
        armorCheck(stage, mReferencables.getArmors(), messages);
        return;
    }

    stage -= mArmorsSzie;

    if (stage < mClothingSize)
    {
        clothingCheck(stage, mReferencables.getClothing(), messages);
        return;
    }

    stage -= mClothingSize;

    if (stage < mContainersSize)
    {
        containerCheck(stage, mReferencables.getContainers(), messages);
        return;
    }

    stage -= mContainersSize;

    if (stage < mDoorsSize)
    {
        doorCheck(stage, mReferencables.getDoors(), messages);
        return;
    }

    stage -= mDoorsSize;
    
    if (stage < mIngredientsSize)
    {
      ingredientCheck(stage, mReferencables.getIngredients(), messages);
      return;
    }
    
    stage -= mIngredientsSize;
}

int CSMTools::ReferenceableCheckStage::setup()
{
    return mReferencables.getSize();
}

void CSMTools::ReferenceableCheckStage::bookCheck(int stage, const CSMWorld::RefIdDataContainer< ESM::Book >& records, std::vector< std::string >& messages)
{
    const CSMWorld::RecordBase& baserecord = records.getRecord(stage);

    if (baserecord.isDeleted())
    {
        return;
    }

    const ESM::Book& Book = (static_cast<const CSMWorld::Record<ESM::Book>& >(baserecord)).get();
    CSMWorld::UniversalId id(CSMWorld::UniversalId::Type_Book, Book.mId);

    //Checking for name
    if (Book.mName.empty())
    {
        messages.push_back(id.toString() + "|" + Book.mId + " has an empty name");
    }

    //Checking for weight
    if (Book.mData.mWeight < 0)
    {
        messages.push_back(id.toString() + "|" + Book.mId + " has negative weight");
    }

    //Checking for value
    if (Book.mData.mValue < 0)
    {
        messages.push_back(id.toString() + "|" + Book.mId + " has negative value");
    }

//checking for model
    if (Book.mModel.empty())
    {
        messages.push_back(id.toString() + "|" + Book.mId + " has no model");
    }

    //checking for icon
    if (Book.mIcon.empty())
    {
        messages.push_back(id.toString() + "|" + Book.mId + " has no icon");
    }

    //checking for enchantment points
    if (Book.mData.mEnchant < 0)
    {
        messages.push_back(id.toString() + "|" + Book.mId + " has negative enchantment");
    }
}

void CSMTools::ReferenceableCheckStage::activatorCheck(int stage, const CSMWorld::RefIdDataContainer< ESM::Activator >& records, std::vector< std::string >& messages)
{
    const CSMWorld::RecordBase& baserecord = records.getRecord(stage);

    if (baserecord.isDeleted())
    {
        return;
    }

    const ESM::Activator& Activator = (static_cast<const CSMWorld::Record<ESM::Activator>& >(baserecord)).get();
    CSMWorld::UniversalId id(CSMWorld::UniversalId::Type_Activator, Activator.mId);

    //Checking for model, IIRC all activators should have a model
    if (Activator.mModel.empty())
    {
        messages.push_back(id.toString() + "|" + Activator.mId + " has no model");
    }
}

void CSMTools::ReferenceableCheckStage::potionCheck(int stage, const CSMWorld::RefIdDataContainer< ESM::Potion >& records, std::vector< std::string >& messages)
{
    const CSMWorld::RecordBase& baserecord = records.getRecord(stage);

    if (baserecord.isDeleted())
    {
        return;
    }

    const ESM::Potion& Potion = (static_cast<const CSMWorld::Record<ESM::Potion>& >(baserecord)).get();
    CSMWorld::UniversalId id(CSMWorld::UniversalId::Type_Potion, Potion.mId);

    //Checking for name
    if (Potion.mName.empty())
    {
        messages.push_back(id.toString() + "|" + Potion.mId + " has an empty name");
    }

    //Checking for weight
    if (Potion.mData.mWeight < 0)
    {
        messages.push_back(id.toString() + "|" + Potion.mId + " has negative weight");
    }

    //Checking for value
    if (Potion.mData.mValue < 0)
    {
        messages.push_back(id.toString() + "|" + Potion.mId + " has negative value");
    }

//checking for model
    if (Potion.mModel.empty())
    {
        messages.push_back(id.toString() + "|" + Potion.mId + " has no model");
    }

    //checking for icon
    if (Potion.mIcon.empty())
    {
        messages.push_back(id.toString() + "|" + Potion.mId + " has no icon");
    }

    //IIRC potion can have empty effects list just fine.
}


void CSMTools::ReferenceableCheckStage::apparatusCheck(int stage, const CSMWorld::RefIdDataContainer< ESM::Apparatus >& records, std::vector< std::string >& messages)
{
    const CSMWorld::RecordBase& baserecord = records.getRecord(stage);

    if (baserecord.isDeleted())
    {
        return;
    }

    const ESM::Apparatus& Apparatus = (static_cast<const CSMWorld::Record<ESM::Apparatus>& >(baserecord)).get();
    CSMWorld::UniversalId id(CSMWorld::UniversalId::Type_Apparatus, Apparatus.mId);

    //Checking for name
    if (Apparatus.mName.empty())
    {
        messages.push_back(id.toString() + "|" + Apparatus.mId + " has an empty name");
    }

    //Checking for weight
    if (Apparatus.mData.mWeight < 0)
    {
        messages.push_back(id.toString() + "|" + Apparatus.mId + " has negative weight");
    }

    //Checking for value
    if (Apparatus.mData.mValue < 0)
    {
        messages.push_back(id.toString() + "|" + Apparatus.mId + " has negative value");
    }

//checking for model
    if (Apparatus.mModel.empty())
    {
        messages.push_back(id.toString() + "|" + Apparatus.mId + " has no model");
    }

    //checking for icon
    if (Apparatus.mIcon.empty())
    {
        messages.push_back(id.toString() + "|" + Apparatus.mId + " has no icon");
    }

    //checking for quality, 0 → apparatus is basicly useless, any negative → apparatus is harmfull instead of helpfull
    if (Apparatus.mData.mQuality <= 0)
    {
        messages.push_back(id.toString() + "|" + Apparatus.mId + " has non-positive quality");
    }
}

void CSMTools::ReferenceableCheckStage::armorCheck(int stage, const CSMWorld::RefIdDataContainer< ESM::Armor >& records, std::vector< std::string >& messages)
{
    const CSMWorld::RecordBase& baserecord = records.getRecord(stage);

    if (baserecord.isDeleted())
    {
        return;
    }

    const ESM::Armor& Armor = (static_cast<const CSMWorld::Record<ESM::Armor>& >(baserecord)).get();
    CSMWorld::UniversalId id(CSMWorld::UniversalId::Type_Armor, Armor.mId);

    //Checking for name
    if (Armor.mName.empty())
    {
        messages.push_back(id.toString() + "|" + Armor.mId + " has an empty name");
    }

    //Checking for weight
    if (Armor.mData.mWeight < 0)
    {
        messages.push_back(id.toString() + "|" + Armor.mId + " has negative weight");
    }

    //Checking for value
    if (Armor.mData.mValue < 0)
    {
        messages.push_back(id.toString() + "|" + Armor.mId + " has negative value");
    }

//checking for model
    if (Armor.mModel.empty())
    {
        messages.push_back(id.toString() + "|" + Armor.mId + " has no model");
    }

    //checking for icon
    if (Armor.mIcon.empty())
    {
        messages.push_back(id.toString() + "|" + Armor.mId + " has no icon");
    }

    //checking for enchantment points
    if (Armor.mData.mEnchant < 0)
    {
        messages.push_back(id.toString() + "|" + Armor.mId + " has negative enchantment");
    }

    //checking for armor class, armor should have poistive armor class, but 0 is considered legal
    if (Armor.mData.mArmor < 0)
    {
        messages.push_back(id.toString() + "|" + Armor.mId + " has negative armor class");
    }

    //checking for health. Only positive numbers are allowed, and 0 is illegal
    if (Armor.mData.mHealth <= 0)
    {
        messages.push_back(id.toString() + "|" + Armor.mId + " has non positive health");
    }
}

void CSMTools::ReferenceableCheckStage::clothingCheck(int stage, const CSMWorld::RefIdDataContainer< ESM::Clothing >& records, std::vector< std::string >& messages)
{
    const CSMWorld::RecordBase& baserecord = records.getRecord(stage);

    if (baserecord.isDeleted())
    {
        return;
    }

    const ESM::Clothing& Clothing = (static_cast<const CSMWorld::Record<ESM::Clothing>& >(baserecord)).get();
    CSMWorld::UniversalId id(CSMWorld::UniversalId::Type_Clothing, Clothing.mId);

    //Checking for name
    if (Clothing.mName.empty())
    {
        messages.push_back(id.toString() + "|" + Clothing.mId + " has an empty name");
    }

    //Checking for weight
    if (Clothing.mData.mWeight < 0)
    {
        messages.push_back(id.toString() + "|" + Clothing.mId + " has negative weight");
    }

    //Checking for value
    if (Clothing.mData.mValue < 0)
    {
        messages.push_back(id.toString() + "|" + Clothing.mId + " has negative value");
    }

//checking for model
    if (Clothing.mModel.empty())
    {
        messages.push_back(id.toString() + "|" + Clothing.mId + " has no model");
    }

    //checking for icon
    if (Clothing.mIcon.empty())
    {
        messages.push_back(id.toString() + "|" + Clothing.mId + " has no icon");
    }

    //checking for enchantment points
    if (Clothing.mData.mEnchant < 0)
    {
        messages.push_back(id.toString() + "|" + Clothing.mId + " has negative enchantment");
    }
}

void CSMTools::ReferenceableCheckStage::containerCheck(int stage, const CSMWorld::RefIdDataContainer< ESM::Container >& records, std::vector< std::string >& messages)
{
    const CSMWorld::RecordBase& baserecord = records.getRecord(stage);

    if (baserecord.isDeleted())
    {
        return;
    }

    const ESM::Container& Container = (static_cast<const CSMWorld::Record<ESM::Container>& >(baserecord)).get();
    CSMWorld::UniversalId id(CSMWorld::UniversalId::Type_Container, Container.mId);

    //Checking for model, IIRC all containers should have a model
    if (Container.mModel.empty())
    {
        messages.push_back(id.toString() + "|" + Container.mId + " has no model");
    }

    //Checking for capacity (weight)
    if (Container.mWeight < 0) //0 is allowed
    {
        messages.push_back(id.toString() + "|" + Container.mId + " has negative weight (capacity)");
    }

    //checking for name
    if (Container.mName.empty())
    {
        messages.push_back(id.toString() + "|" + Container.mId + " has an empty name");
    }
}

void CSMTools::ReferenceableCheckStage::creatureCheck(int stage, const CSMWorld::RefIdDataContainer< ESM::Creature >& records, std::vector< std::string >& messages)
{
    const CSMWorld::RecordBase& baserecord = records.getRecord(stage);

    if (baserecord.isDeleted())
    {
        return;
    }

    const ESM::Creature& Creature = (static_cast<const CSMWorld::Record<ESM::Creature>&>(baserecord)).get();
    CSMWorld::UniversalId id(CSMWorld::UniversalId::Type_Creature, Creature.mId);

    if (Creature.mModel.empty())
    {
        messages.push_back(id.toString() + "|" + Creature.mId + " has no model");
    }

    if (Creature.mName.empty())
    {
        messages.push_back(id.toString() + "|" + Creature.mId + " has an empty name");
    }

    //stats checks
    if (Creature.mData.mLevel < 1)
    {
        messages.push_back(id.toString() + "|" + Creature.mId + " has non-postive level");
    }

    if (Creature.mData.mStrength < 0)
    {
        messages.push_back(id.toString() + "|" + Creature.mId + " has negative strength");
    }

    if (Creature.mData.mIntelligence < 0)
    {
        messages.push_back(id.toString() + "|" + Creature.mId + " has negative intelligence");
    }

    if (Creature.mData.mWillpower < 0)
    {
        messages.push_back(id.toString() + "|" + Creature.mId + " has negative willpower");
    }

    if (Creature.mData.mAgility < 0)
    {
        messages.push_back(id.toString() + "|" + Creature.mId + " has negative agility");
    }

    if (Creature.mData.mSpeed < 0)
    {
        messages.push_back(id.toString() + "|" + Creature.mId + " has negative speed");
    }

    if (Creature.mData.mEndurance < 0)
    {
        messages.push_back(id.toString() + "|" + Creature.mId + " has negative endurance");
    }

    if (Creature.mData.mPersonality < 0)
    {
        messages.push_back(id.toString() + "|" + Creature.mId + " has negative personality");
    }

    if (Creature.mData.mLuck < 0)
    {
        messages.push_back(id.toString() + "|" + Creature.mId + " has negative luck");
    }

    if (Creature.mData.mHealth < 0)
    {
        messages.push_back(id.toString() + "|" + Creature.mId + " has negative health");
    }

    if (Creature.mData.mSoul < 0)
    {
        messages.push_back(id.toString() + "|" + Creature.mId + " has negative soul value");
    }

    for (int i = 0; i < 6; ++i)
    {
        if (Creature.mData.mAttack[i] < 0)
        {
            messages.push_back(id.toString() + "|" + Creature.mId + " has negative attack strength");
            break;
        }
    }

    //TODO, find meaning of other values
    if (Creature.mData.mGold < 0) //It seems that this is for gold in merchant creatures
    {
        messages.push_back(id.toString() + "|" + Creature.mId + " has negative gold ");
    }
}

void CSMTools::ReferenceableCheckStage::doorCheck(int stage, const CSMWorld::RefIdDataContainer< ESM::Door >& records, std::vector< std::string >& messages)
{
    const CSMWorld::RecordBase& baserecord = records.getRecord(stage);

    if (baserecord.isDeleted())
    {
        return;
    }

    const ESM::Door& Door = (static_cast<const CSMWorld::Record<ESM::Door>&>(baserecord)).get();
    CSMWorld::UniversalId id(CSMWorld::UniversalId::Type_Door, Door.mId);

    //usual, name and model
    if (Door.mName.empty())
    {
        messages.push_back(id.toString() + "|" + Door.mId + " has an empty name");
    }

    if (Door.mModel.empty())
    {
        messages.push_back(id.toString() + "|" + Door.mId + " has no model");
    }

    //TODO, check what static unsigned int sRecordId; is for
}

void CSMTools::ReferenceableCheckStage::ingredientCheck(int stage, const CSMWorld::RefIdDataContainer< ESM::Ingredient >& records, std::vector< std::string >& messages)
{
    const CSMWorld::RecordBase& baserecord = records.getRecord(stage);

    if (baserecord.isDeleted())
    {
        return;
    }

    const ESM::Ingredient& Ingredient = (static_cast<const CSMWorld::Record<ESM::Ingredient>& >(baserecord)).get();
    CSMWorld::UniversalId id(CSMWorld::UniversalId::Type_Ingredient, Ingredient.mId);

    //Checking for name
    if (Ingredient.mName.empty())
    {
        messages.push_back(id.toString() + "|" + Ingredient.mId + " has an empty name");
    }

    //Checking for weight
    if (Ingredient.mData.mWeight < 0)
    {
        messages.push_back(id.toString() + "|" + Ingredient.mId + " has negative weight");
    }

    //Checking for value
    if (Ingredient.mData.mValue < 0)
    {
        messages.push_back(id.toString() + "|" + Ingredient.mId + " has negative value");
    }

//checking for model
    if (Ingredient.mModel.empty())
    {
        messages.push_back(id.toString() + "|" + Ingredient.mId + " has no model");
    }

    //checking for icon
    if (Ingredient.mIcon.empty())
    {
        messages.push_back(id.toString() + "|" + Ingredient.mId + " has no icon");
    }
}

void CSMTools::ReferenceableCheckStage::creaturesLevListCheck(int stage, const CSMWorld::RefIdDataContainer< ESM::CreatureLevList >& records, std::vector< std::string >& messages)
{
      const CSMWorld::RecordBase& baserecord = records.getRecord(stage);

    if (baserecord.isDeleted())
    {
        return;
    }

    const ESM::CreatureLevList& CreatureLevList = (static_cast<const CSMWorld::Record<ESM::CreatureLevList>& >(baserecord)).get();
    CSMWorld::UniversalId id(CSMWorld::UniversalId::Type_CreatureLevList, CreatureLevList.mId);
    
    //TODO(!)
}