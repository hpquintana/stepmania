#ifndef FONT_H
#define FONT_H
/*
-----------------------------------------------------------------------------
 File: Font

 Desc: A holder for information that is used by BitmapText objects.

 Copyright (c) 2001-2002 by the person(s) listed below.  All rights reserved.
	Chris Danford
-----------------------------------------------------------------------------
*/

#include "RageTexture.h"
#include "IniFile.h"

struct glyph {
	RageTexture *Texture;

	/* Number of pixels to advance horizontally after drawing this character. */
	int hadvance, vadvance;

	/* Size of the actual rendered character. */
	float width, height;

	/* Number of pixels to offset this character when rendering. */
	float hshift, vshift;

	/* Texture coordinate rect. */
	RectF rect;
};

class FontPage
{
public:
	RageTexture* m_pTexture;

	CString m_sTexturePath;

	/* All glyphs in this list will point to m_pTexture. */
	vector<glyph> glyphs;

	map<int,int> m_iCharToGlyphNo;

	FontPage();
	~FontPage();

	int GetLineWidthInSourcePixels( const CString &szLine );
	int GetLineHeightInSourcePixels( const CString &szLine );

	void Load( const CString &sASCIITexturePath, IniFile &ini );

private:
	void SetExtraPixels(int DrawExtraPixelsLeft, int DrawExtraPixelsRight);
	void SetTextureCoords(const vector<int> &widths, int LineSpacing);
};

class Font
{
public:
	int m_iRefCount;
	CString path;
	map<int,glyph*> m_iCharToGlyph;

	Font();

	RageTexture *GetGlyphTexture( int c );
	const glyph &GetGlyph( int c ) const;

	int GetLineWidthInSourcePixels( const CString &szLine ) const;
	int GetLineHeightInSourcePixels( const CString &szLine ) const;

	/* Add a FontPage to this font. */
	void AddPage(FontPage *fp);

	/* Load font-wide settings. */
	void LoadINI(IniFile &ini);

private:
	vector<FontPage *> pages;
};

#endif
