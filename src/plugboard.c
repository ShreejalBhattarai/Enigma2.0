// ───── PLUGBOARD MODULE ─────

void set_plugboard(void) {
    printf("[Plugboard] Set plugboard pairs (mock).\n");
}

void apply_plugboard_mapping(char *ch) {
    // Example: A↔M, B↔N, C↔O
    if (!isalpha(*ch)) return;

    switch (toupper(*ch)) {
        case 'A': *ch = 'M'; break;
        case 'M': *ch = 'A'; break;
        case 'B': *ch = 'N'; break;
        case 'N': *ch = 'B'; break;
        case 'C': *ch = 'O'; break;
        case 'O': *ch = 'C'; break;
        default: break;
    }
}

void reverse_plugboard_mapping(char *ch) {
    // Plugboard is symmetric in Enigma
    apply_plugboard_mapping(ch);
}

void reset_plugboard(void) {
    printf("[Plugboard] Plugboard mappings cleared.\n");
}