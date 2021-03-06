#include "loadlock.hpp"

#include "esmreader.hpp"
#include "esmwriter.hpp"
#include "defs.hpp"

namespace ESM
{
    unsigned int Lockpick::sRecordId = REC_LOCK;

    void Lockpick::load(ESMReader &esm)
    {
        bool hasData = true;
        while (esm.hasMoreSubs())
        {
            esm.getSubName();
            uint32_t name = esm.retSubName().val;
            switch (name)
            {
                case ESM::FourCC<'M','O','D','L'>::value:
                    mModel = esm.getHString();
                    break;
                case ESM::FourCC<'F','N','A','M'>::value:
                    mName = esm.getHString();
                    break;
                case ESM::FourCC<'L','K','D','T'>::value:
                    esm.getHT(mData, 16);
                    hasData = true;
                    break;
                case ESM::FourCC<'S','C','R','I'>::value:
                    mScript = esm.getHString();
                    break;
                case ESM::FourCC<'I','T','E','X'>::value:
                    mIcon = esm.getHString();
                    break;
                default:
                    esm.fail("Unknown subrecord");
            }
        }
        if (!hasData)
            esm.fail("Missing LKDT subrecord");
    }

    void Lockpick::save(ESMWriter &esm) const
    {
        esm.writeHNCString("MODL", mModel);
        esm.writeHNOCString("FNAM", mName);

        esm.writeHNT("LKDT", mData, 16);
        esm.writeHNOString("SCRI", mScript);
        esm.writeHNOCString("ITEX", mIcon);
    }

    void Lockpick::blank()
    {
        mData.mWeight = 0;
        mData.mValue = 0;
        mData.mQuality = 0;
        mData.mUses = 0;
        mName.clear();
        mModel.clear();
        mIcon.clear();
        mScript.clear();
    }
}
