// Utility

    // @return bool True if saved, False if unable to save
    // ========================================================================
    bool TGA_Save32( int width, int height, void *pix, size_t len, const char *filename )
    {
        bool bSuccess = false;

        FILE *pFile = fopen( filename, "w+b" );
        if( pFile )
        {
            putc( 0, pFile ); // [00] Number of Characters in Identification Field.
            putc( 0, pFile ); // [01] Color Map Type
            putc( 2, pFile ); // [02] Image Type Code: 2 = uncompressed RGB

            putc( 0, pFile ); // [03] Color Map Specification 
            putc( 0, pFile );
            putc( 0, pFile ); 
            putc( 0, pFile );
            putc( 0, pFile );

            putc( 0, pFile ); putc( 0, pFile ); // [08] X origin
            putc( 0, pFile ); putc( 0, pFile ); // [10] y origin

            putc( (width >>  0) & 0xFF, pFile ); // [12] 16-bit width
            putc( (width >> 16) & 0xFF, pFile );

            putc( (height >>  0) & 0xFF, pFile ); // [14] 16-bit height
            putc( (height >> 16) & 0xFF, pFile );

            putc( 32, pFile ); // [16] Bits Per Pixel = 32 bit
            putc( 32, pFile ); // [17] Image Descriptor Byte: (1<<5) Origin Top Left

            size_t wrote = fwrite( pix, 1, len, pFile );
            bSuccess = wrote == len;

            fclose( pFile );
        }

        return bSuccess;
    }

