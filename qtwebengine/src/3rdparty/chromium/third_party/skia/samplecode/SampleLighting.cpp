/*
 * Copyright 2015 Google Inc.
 *
 * Use of this source code is governed by a BSD-style license that can be
 * found in the LICENSE file.
 */

#include "DecodeFile.h"
#include "SampleCode.h"
#include "Resources.h"
#include "SkCanvas.h"
#include "SkLightingShader.h"
#include "SkNormalSource.h"
#include "SkPoint3.h"

static sk_sp<SkLights> create_lights(SkScalar angle, SkScalar blue) {

    const SkVector3 dir = SkVector3::Make(SkScalarSin(angle)*SkScalarSin(SK_ScalarPI*0.25f),
                                          SkScalarCos(angle)*SkScalarSin(SK_ScalarPI*0.25f),
                                          SkScalarCos(SK_ScalarPI*0.25f));

    SkLights::Builder builder;

    builder.add(SkLights::Light::MakeDirectional(SkColor3f::Make(1.0f, 1.0f, blue), dir));
    builder.setAmbientLightColor(SkColor3f::Make(0.1f, 0.1f, 0.1f));

    return builder.finish();
}

////////////////////////////////////////////////////////////////////////////

class LightingView : public SampleView {
public:
    LightingView() : fLightAngle(0.0f) , fColorFactor(0.0f) {
        {
            SkBitmap diffuseBitmap;
            SkAssertResult(GetResourceAsBitmap("images/brickwork-texture.jpg", &diffuseBitmap));

            fRect = SkRect::MakeIWH(diffuseBitmap.width(), diffuseBitmap.height());

            fDiffuseShader = SkShader::MakeBitmapShader(diffuseBitmap,
                                                        SkShader::kClamp_TileMode,
                                                        SkShader::kClamp_TileMode,
                                                        nullptr);
        }

        {
            SkBitmap normalBitmap;
            SkAssertResult(GetResourceAsBitmap("images/brickwork_normal-map.jpg", &normalBitmap));

            sk_sp<SkShader> normalMap = SkShader::MakeBitmapShader(normalBitmap,
                                                                   SkShader::kClamp_TileMode,
                                                                   SkShader::kClamp_TileMode,
                                                                   nullptr);
            fNormalSource = SkNormalSource::MakeFromNormalMap(std::move(normalMap), SkMatrix::I());
        }
    }

protected:
    // overrides from SkEventSink
    bool onQuery(SkEvent* evt) override {
        if (SampleCode::TitleQ(*evt)) {
            SampleCode::TitleR(evt, "Lighting");
            return true;
        }
        return this->INHERITED::onQuery(evt);
    }

    void onDrawContent(SkCanvas* canvas) override {
        sk_sp<SkLights> lights(create_lights(fLightAngle, fColorFactor));

        SkPaint paint;
        paint.setShader(SkLightingShader::Make(fDiffuseShader,
                                               fNormalSource,
                                               std::move(lights)));
        paint.setColor(SK_ColorBLACK);

        canvas->drawRect(fRect, paint);
    }

    SkView::Click* onFindClickHandler(SkScalar x, SkScalar y, unsigned modi) override {
        return this->INHERITED::onFindClickHandler(x, y, modi);
    }

    bool onAnimate(const SkAnimTimer& timer) override {
        fLightAngle += 0.015f;
        fColorFactor += 0.01f;
        if (fColorFactor > 1.0f) {
            fColorFactor = 0.0f;
        }

        return true;
    }

private:
    SkRect                fRect;
    sk_sp<SkShader>       fDiffuseShader;
    sk_sp<SkNormalSource> fNormalSource;

    SkScalar              fLightAngle;
    SkScalar              fColorFactor;

    typedef SampleView INHERITED;
};

//////////////////////////////////////////////////////////////////////////////

static SkView* MyFactory() { return new LightingView; }
static SkViewRegister reg(MyFactory);
