#ifndef     MSUD_DATA_H
#define     MSUD_DATA_H

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
struct msud_input_t
{
    msud_input_t()
    {

    }
};

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
struct msud_output_t
{
    // Подача питания на реле КМ23
    bool kv23_on;

    msud_output_t()
        : kv23_on(false)
    {

    }
};

#endif // MSUD_DATA_H
