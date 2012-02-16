// Copyright (c) 2010-2011 Zipline Games, Inc. All Rights Reserved.
// http://getmoai.com

#include "pch.h"
#include <uslscore/USBox.h>
#include <uslscore/USPrism.h>

//================================================================//
// USBox
//================================================================//

//----------------------------------------------------------------//
float USBox::Area () const {

	return ( this->mMax.mX - this->mMin.mX ) * ( this->mMax.mY - this->mMin.mY ) * ( this->mMax.mZ - this->mMin.mZ );
}

//----------------------------------------------------------------//
void USBox::Bless () {

	if ( this->mMin.mX > this->mMax.mX ) {
		float temp = this->mMin.mX;
		this->mMin.mX = this->mMax.mX;
		this->mMax.mX = temp;
	}
	
	if ( this->mMin.mY > this->mMax.mY ) {
		float temp = this->mMin.mY;
		this->mMin.mY = this->mMax.mY;
		this->mMax.mY = temp;
	}
	
	if ( this->mMin.mZ > this->mMax.mZ ) {
		float temp = this->mMin.mZ;
		this->mMin.mZ = this->mMax.mZ;
		this->mMax.mZ = temp;
	}
}

//----------------------------------------------------------------//
void USBox::Clip ( const USBox& box ) {

	// Clamp XMin
	if ( this->mMin.mX < box.mMin.mX ) this->mMin.mX = box.mMin.mX;
	if ( this->mMin.mX > box.mMax.mX ) this->mMin.mX = box.mMax.mX;
	
	// Clamp XMax
	if ( this->mMax.mX < box.mMin.mX ) this->mMax.mX = box.mMin.mX;
	if ( this->mMax.mX > box.mMax.mX ) {
		this->mMax.mX = box.mMax.mX;
	}
	
	// Clamp YMin
	if ( this->mMin.mY < box.mMin.mY ) this->mMin.mY = box.mMin.mY;
	if ( this->mMin.mY > box.mMax.mY ) this->mMin.mY = box.mMax.mY;
	
	// Clamp YMax
	if ( this->mMax.mY < box.mMin.mY ) this->mMax.mY = box.mMin.mY;
	if ( this->mMax.mY > box.mMax.mY ) this->mMax.mY = box.mMax.mY;
	
	// Clamp ZMin
	if ( this->mMin.mZ < box.mMin.mZ ) this->mMin.mZ = box.mMin.mZ;
	if ( this->mMin.mZ > box.mMax.mZ ) this->mMin.mZ = box.mMax.mZ;
	
	// Clamp ZMax
	if ( this->mMax.mZ < box.mMin.mZ ) this->mMax.mZ = box.mMin.mZ;
	if ( this->mMax.mZ > box.mMax.mZ ) this->mMax.mZ = box.mMax.mZ;
}

//----------------------------------------------------------------//
bool USBox::Contains ( const USVec3D& loc ) const {

	if (( loc.mX < mMin.mX ) || ( loc.mX > mMax.mX )) return false;
	if (( loc.mY < mMin.mY ) || ( loc.mY > mMax.mY )) return false;
	if (( loc.mZ < mMin.mZ ) || ( loc.mZ > mMax.mZ )) return false;
	
	return true;
}

//----------------------------------------------------------------//
bool USBox::ContainsX ( float x ) const {
	
	if ( x < this->mMin.mX ) return false;
	if ( x > this->mMax.mX ) return false;
	
	return true;
}

//----------------------------------------------------------------//
bool USBox::ContainsY ( float y ) const {
	
	if ( y < this->mMin.mY ) return false;
	if ( y > this->mMax.mY ) return false;
	
	return true;
}

//----------------------------------------------------------------//
bool USBox::ContainsZ ( float z ) const {
	
	if ( z < this->mMin.mZ ) return false;
	if ( z > this->mMax.mZ ) return false;
	
	return true;
}

//----------------------------------------------------------------//
void USBox::GetCenter ( USVec3D& center ) const {
	
	center.mX = this->mMin.mX + (( this->mMax.mX - this->mMin.mX ) * 0.5f );
	center.mY = this->mMin.mY + (( this->mMax.mY - this->mMin.mY ) * 0.5f );
	center.mZ = this->mMin.mZ + (( this->mMax.mZ - this->mMin.mZ ) * 0.5f );
}

//----------------------------------------------------------------//
float USBox::GetRadius () const {

	USVec3D spans = mMax;
	spans.Sub ( mMin );
	spans.Scale ( 0.5f );
	return spans.Length ();
}

//----------------------------------------------------------------//
void USBox::GetRectXY ( USRect& rect ) const {
	
	rect.mXMin = this->mMin.mX;
	rect.mXMax = this->mMax.mX;
	
	rect.mYMin = this->mMin.mY;
	rect.mYMax = this->mMax.mY;
}

//----------------------------------------------------------------//
void USBox::GetRectXZ ( USRect& rect ) const {

	rect.mXMin = this->mMin.mX;
	rect.mXMax = this->mMax.mX;
	
	rect.mYMin = this->mMin.mZ;
	rect.mYMax = this->mMax.mZ;
}

//----------------------------------------------------------------//
void USBox::GetRectZY ( USRect& rect ) const {

	rect.mXMin = this->mMin.mZ;
	rect.mXMax = this->mMax.mZ;
	
	rect.mYMin = this->mMin.mY;
	rect.mYMax = this->mMax.mY;
}

//----------------------------------------------------------------//
void USBox::Grow ( const USBox& box ) {

	if ( mMin.mX > box.mMin.mX ) mMin.mX = box.mMin.mX;
	if ( mMax.mX < box.mMax.mX ) mMax.mX = box.mMax.mX;
	
	if ( mMin.mY > box.mMin.mY ) mMin.mY = box.mMin.mY;
	if ( mMax.mY < box.mMax.mY ) mMax.mY = box.mMax.mY;
	
	if ( mMin.mZ > box.mMin.mZ ) mMin.mZ = box.mMin.mZ;
	if ( mMax.mZ < box.mMax.mZ ) mMax.mZ = box.mMax.mZ;
}

//----------------------------------------------------------------//
void USBox::Grow ( const USVec3D& vec ) {

	if ( mMin.mX > vec.mX ) mMin.mX = vec.mX;
	else if ( mMax.mX < vec.mX ) mMax.mX = vec.mX;
	
	if ( mMin.mY > vec.mY ) mMin.mY = vec.mY;
	else if ( mMax.mY < vec.mY ) mMax.mY = vec.mY;

	if ( mMin.mZ > vec.mZ ) mMin.mZ = vec.mZ;
	else if ( mMax.mZ < vec.mZ ) mMax.mZ = vec.mZ;
}

//----------------------------------------------------------------//
void USBox::Init ( const USBox& box ) {

	*this = box;
}

//----------------------------------------------------------------//
void USBox::Init ( const USVec3D& vec ) {

	mMin.mX = mMax.mX = vec.mX;
	mMin.mY = mMax.mY = vec.mY;
	mMin.mZ = mMax.mZ = vec.mZ;
}

//----------------------------------------------------------------//
void USBox::Init ( float left, float top, float right, float bottom, float back, float front ) {

	this->mMin.mX = left;
	this->mMax.mX = right;

	this->mMax.mY = top;
	this->mMin.mY = bottom;
	
	this->mMin.mZ = back;
	this->mMax.mZ = front;
}

//----------------------------------------------------------------//
bool USBox::Overlap ( const USBox& box ) const {

	if ( mMin.mX > box.mMax.mX ) return false;
	if ( mMax.mX < box.mMin.mX ) return false;
	
	if ( mMin.mY > box.mMax.mY ) return false;
	if ( mMax.mY < box.mMin.mY ) return false;
	
	if ( mMin.mZ > box.mMax.mZ ) return false;
	if ( mMax.mZ < box.mMin.mZ ) return false;
	
	return true;
}

//----------------------------------------------------------------//
bool USBox::OverlapXY ( const USBox& box ) const {

	if ( mMin.mX > box.mMax.mX ) return false;
	if ( mMax.mX < box.mMin.mX ) return false;
	
	if ( mMin.mY > box.mMax.mY ) return false;
	if ( mMax.mY < box.mMin.mY ) return false;
	
	return true;
}

//----------------------------------------------------------------//
bool USBox::OverlapXZ ( const USBox& box ) const {

	if ( mMin.mX > box.mMax.mX ) return false;
	if ( mMax.mX < box.mMin.mX ) return false;
	
	if ( mMin.mZ > box.mMax.mZ ) return false;
	if ( mMax.mZ < box.mMin.mZ ) return false;
	
	return true;
}

//----------------------------------------------------------------//
bool USBox::OverlapZY ( const USBox& box ) const {
	
	if ( mMin.mY > box.mMax.mY ) return false;
	if ( mMax.mY < box.mMin.mY ) return false;
	
	if ( mMin.mZ > box.mMax.mZ ) return false;
	if ( mMax.mZ < box.mMin.mZ ) return false;
	
	return true;
}

//----------------------------------------------------------------//
void USBox::Pad ( float pad ) {

	this->mMin.mX -= pad;
	this->mMin.mY -= pad;
	this->mMin.mZ -= pad;

	this->mMax.mX += pad;
	this->mMax.mY += pad;
	this->mMax.mZ += pad;	
}

//----------------------------------------------------------------//
void USBox::Scale ( float scale ) {

	mMin.mX *= scale;
	mMax.mX *= scale;

	mMin.mY *= scale;
	mMax.mY *= scale;

	mMin.mZ *= scale;
	mMax.mZ *= scale;
}

//----------------------------------------------------------------//
void USBox::Transform ( const USMatrix4x4& mtx ) {

	USPrism prism;
	prism.Init ( *this );
	prism.Transform ( mtx );
	
	this->mMin = prism.mLoc;
	this->mMax = prism.mLoc;
	
	// X Axis
	if ( prism.mXAxis.mX < 0.0f )	this->mMin.mX += prism.mXAxis.mX;
	else							this->mMax.mX += prism.mXAxis.mX;
	
	if ( prism.mYAxis.mX < 0.0f )	this->mMin.mX += prism.mYAxis.mX;
	else							this->mMax.mX += prism.mYAxis.mX;
	
	if ( prism.mZAxis.mX < 0.0f )	this->mMin.mX += prism.mZAxis.mX;
	else							this->mMax.mX += prism.mZAxis.mX;
	
	// Y Axis
	if ( prism.mXAxis.mY < 0.0f )	this->mMin.mY += prism.mXAxis.mY;
	else							this->mMax.mY += prism.mXAxis.mY;
	
	if ( prism.mYAxis.mY < 0.0f )	this->mMin.mY += prism.mYAxis.mY;
	else							this->mMax.mY += prism.mYAxis.mY;
	
	if ( prism.mZAxis.mY < 0.0f )	this->mMin.mY += prism.mZAxis.mY;
	else							this->mMax.mY += prism.mZAxis.mY;
	
	// Z Axis
	if ( prism.mXAxis.mZ < 0.0f )	this->mMin.mZ += prism.mXAxis.mZ;
	else							this->mMax.mZ += prism.mXAxis.mZ;
	
	if ( prism.mYAxis.mZ < 0.0f )	this->mMin.mZ += prism.mYAxis.mZ;
	else							this->mMax.mZ += prism.mYAxis.mZ;
	
	if ( prism.mZAxis.mZ < 0.0f )	this->mMin.mZ += prism.mZAxis.mZ;
	else							this->mMax.mZ += prism.mZAxis.mZ;
}
