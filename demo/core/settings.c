
	#include "settings.h"

	settings * settings_construct(void) {

		settings * sets;

		sets = (settings *) malloc(sizeof(settings));
				
		return sets;

	}

	void settings_destroy(settings * sets) {

		free((void *) sets);

	}

	void settings_load(settings * sets, const char * file) {

		json_tokens * tokens;
		char * line;
		char * string;
		FILE * fp;

		unsigned int nTokens = 1024;
		unsigned int nBytesPerLine = 1024;
		unsigned int nBytesPerString = 65536;

		int parseRtn;

		int token_root_O;

		int token_root_raw_V;
		int token_root_raw_O;

		int token_root_raw_format_V;
		int token_root_raw_format_O;
		int token_root_raw_format_fS_V;
		int token_root_raw_format_fS_N;
		int token_root_raw_format_hopSize_V;
		int token_root_raw_format_hopSize_N;
		int token_root_raw_format_nBits_V;
		int token_root_raw_format_nBits_N;

		int token_root_raw_nChannels_V;
		int token_root_raw_nChannels_N;

		int token_root_raw_input_V;
		int token_root_raw_input_O;
		int token_root_raw_input_type_V;
		int token_root_raw_input_type_S;
		int token_root_raw_input_file_V;
		int token_root_raw_input_file_O;
		int token_root_raw_input_file_path_V;
		int token_root_raw_input_file_path_S;
		int token_root_raw_input_socket_V;
		int token_root_raw_input_socket_O;
		int token_root_raw_input_socket_port_V;
		int token_root_raw_input_socket_port_N;
		int token_root_raw_input_soundcard_V;
		int token_root_raw_input_soundcard_O;
		int token_root_raw_input_soundcard_device_V;
		int token_root_raw_input_soundcard_device_S;
		
		int token_root_raw_output_V;
		int token_root_raw_output_O;
		int token_root_raw_output_type_V;
		int token_root_raw_output_type_S;
		int token_root_raw_output_file_V;
		int token_root_raw_output_file_O;
		int token_root_raw_output_file_path_V;
		int token_root_raw_output_file_path_S;
		int token_root_raw_output_socket_V;
		int token_root_raw_output_socket_O;
		int token_root_raw_output_socket_port_V;
		int token_root_raw_output_socket_port_N;	

		int token_root_mapping_V;
		int token_root_mapping_O;

		int token_root_mapping_map_V;
		int token_root_mapping_map_A;
		int token_root_mapping_map_e_V[SETTINGS_NCHANNELS];
		int token_root_mapping_map_e_N[SETTINGS_NCHANNELS];

		int token_root_general_V;
		int token_root_general_O;
		
		int token_root_general_epsilon_V;
		int token_root_general_epsilon_N;
		
		int token_root_general_size_V;
		int token_root_general_size_O;
		int token_root_general_size_hopSize_V;
		int token_root_general_size_hopSize_N;
		int token_root_general_size_frameSize_V;
		int token_root_general_size_frameSize_N;
		
		int token_root_general_samplerate_V;
		int token_root_general_samplerate_O;
		int token_root_general_samplerate_mu_V;
		int token_root_general_samplerate_mu_N;
		int token_root_general_samplerate_sigma2_V;
		int token_root_general_samplerate_sigma2_N;
		
		int token_root_general_speedofsound_V;
		int token_root_general_speedofsound_O;
		int token_root_general_speedofsound_mu_V;
		int token_root_general_speedofsound_mu_N;
		int token_root_general_speedofsound_sigma2_V;
		int token_root_general_speedofsound_sigma2_N;
		
		int token_root_general_mics_V;
		int token_root_general_mics_A;
		int token_root_general_mics_e_V[SETTINGS_NMICS];
		int token_root_general_mics_e_O[SETTINGS_NMICS];
		int token_root_general_mics_e_mus_V[SETTINGS_NMICS];
		int token_root_general_mics_e_mus_A[SETTINGS_NMICS];
		int token_root_general_mics_e_mus_0_V[SETTINGS_NMICS];
		int token_root_general_mics_e_mus_0_N[SETTINGS_NMICS];
		int token_root_general_mics_e_mus_1_V[SETTINGS_NMICS];
		int token_root_general_mics_e_mus_1_N[SETTINGS_NMICS];
		int token_root_general_mics_e_mus_2_V[SETTINGS_NMICS];
		int token_root_general_mics_e_mus_2_N[SETTINGS_NMICS];
		int token_root_general_mics_e_sigma2s_V[SETTINGS_NMICS];
		int token_root_general_mics_e_sigma2s_A[SETTINGS_NMICS];
		int token_root_general_mics_e_sigma2s_0_V[SETTINGS_NMICS];
		int token_root_general_mics_e_sigma2s_0_N[SETTINGS_NMICS];
		int token_root_general_mics_e_sigma2s_1_V[SETTINGS_NMICS];
		int token_root_general_mics_e_sigma2s_1_N[SETTINGS_NMICS];
		int token_root_general_mics_e_sigma2s_2_V[SETTINGS_NMICS];
		int token_root_general_mics_e_sigma2s_2_N[SETTINGS_NMICS];
		int token_root_general_mics_e_sigma2s_3_V[SETTINGS_NMICS];
		int token_root_general_mics_e_sigma2s_3_N[SETTINGS_NMICS];
		int token_root_general_mics_e_sigma2s_4_V[SETTINGS_NMICS];
		int token_root_general_mics_e_sigma2s_4_N[SETTINGS_NMICS];
		int token_root_general_mics_e_sigma2s_5_V[SETTINGS_NMICS];
		int token_root_general_mics_e_sigma2s_5_N[SETTINGS_NMICS];
		int token_root_general_mics_e_sigma2s_6_V[SETTINGS_NMICS];
		int token_root_general_mics_e_sigma2s_6_N[SETTINGS_NMICS];
		int token_root_general_mics_e_sigma2s_7_V[SETTINGS_NMICS];
		int token_root_general_mics_e_sigma2s_7_N[SETTINGS_NMICS];
		int token_root_general_mics_e_sigma2s_8_V[SETTINGS_NMICS];
		int token_root_general_mics_e_sigma2s_8_N[SETTINGS_NMICS];
		int token_root_general_mics_e_directions_V[SETTINGS_NMICS];
		int token_root_general_mics_e_directions_A[SETTINGS_NMICS];
		int token_root_general_mics_e_directions_0_V[SETTINGS_NMICS];
		int token_root_general_mics_e_directions_0_N[SETTINGS_NMICS];
		int token_root_general_mics_e_directions_1_V[SETTINGS_NMICS];
		int token_root_general_mics_e_directions_1_N[SETTINGS_NMICS];
		int token_root_general_mics_e_directions_2_V[SETTINGS_NMICS];
		int token_root_general_mics_e_directions_2_N[SETTINGS_NMICS];
		int token_root_general_mics_e_angles_V[SETTINGS_NMICS];
		int token_root_general_mics_e_angles_A[SETTINGS_NMICS];
		int token_root_general_mics_e_angles_0_V[SETTINGS_NMICS];
		int token_root_general_mics_e_angles_0_N[SETTINGS_NMICS];
		int token_root_general_mics_e_angles_1_V[SETTINGS_NMICS];
		int token_root_general_mics_e_angles_1_N[SETTINGS_NMICS];

		int token_root_general_spatialfilters_V;
		int token_root_general_spatialfilters_A;
		int token_root_general_spatialfilters_e_V[SETTINGS_NSPATIALFILTERS];
		int token_root_general_spatialfilters_e_O[SETTINGS_NSPATIALFILTERS];
		int token_root_general_spatialfilters_e_directions_V[SETTINGS_NSPATIALFILTERS];
		int token_root_general_spatialfilters_e_directions_A[SETTINGS_NSPATIALFILTERS];
		int token_root_general_spatialfilters_e_directions_0_V[SETTINGS_NSPATIALFILTERS];
		int token_root_general_spatialfilters_e_directions_0_N[SETTINGS_NSPATIALFILTERS];
		int token_root_general_spatialfilters_e_directions_1_V[SETTINGS_NSPATIALFILTERS];
		int token_root_general_spatialfilters_e_directions_1_N[SETTINGS_NSPATIALFILTERS];
		int token_root_general_spatialfilters_e_directions_2_V[SETTINGS_NSPATIALFILTERS];
		int token_root_general_spatialfilters_e_directions_2_N[SETTINGS_NSPATIALFILTERS];
		int token_root_general_spatialfilters_e_angles_V[SETTINGS_NSPATIALFILTERS];
		int token_root_general_spatialfilters_e_angles_A[SETTINGS_NSPATIALFILTERS];
		int token_root_general_spatialfilters_e_angles_0_V[SETTINGS_NSPATIALFILTERS];
		int token_root_general_spatialfilters_e_angles_0_N[SETTINGS_NSPATIALFILTERS];
		int token_root_general_spatialfilters_e_angles_1_V[SETTINGS_NSPATIALFILTERS];
		int token_root_general_spatialfilters_e_angles_1_N[SETTINGS_NSPATIALFILTERS];

		int token_root_general_nthetas_V;
		int token_root_general_nthetas_N;
		int token_root_general_gainmin_V;
		int token_root_general_gainmin_N;

		int token_root_sne_V;
		int token_root_sne_O;

		int token_root_sne_b_V;
		int token_root_sne_b_N;
		int token_root_sne_alphaS_V;
		int token_root_sne_alphaS_N;
		int token_root_sne_L_V;
		int token_root_sne_L_N;
		int token_root_sne_delta_V;
		int token_root_sne_delta_N;
		int token_root_sne_alphaD_V;
		int token_root_sne_alphaD_N;

		int token_root_ssl_V;
		int token_root_ssl_O;

		int token_root_ssl_nPots_V;
		int token_root_ssl_nPots_N;
		int token_root_ssl_nMatches_V;
		int token_root_ssl_nMatches_N;
		int token_root_ssl_probMin_V;
		int token_root_ssl_probMin_N;
		int token_root_ssl_nRefinedLevels_V;
		int token_root_ssl_nRefinedLevels_N;
		int token_root_ssl_interpRate_V;
		int token_root_ssl_interpRate_N;

		int token_root_ssl_scans_V;
		int token_root_ssl_scans_A;
		int token_root_ssl_scans_e_V[SETTINGS_NSCANS];
		int token_root_ssl_scans_e_O[SETTINGS_NSCANS];
		int token_root_ssl_scans_e_level_V[SETTINGS_NSCANS];
		int token_root_ssl_scans_e_level_N[SETTINGS_NSCANS];
		int token_root_ssl_scans_e_delta_V[SETTINGS_NSCANS];
		int token_root_ssl_scans_e_delta_N[SETTINGS_NSCANS];

		int token_root_ssl_output_V;
		int token_root_ssl_output_O;
		int token_root_ssl_output_type_V;
		int token_root_ssl_output_type_S;
		int token_root_ssl_output_file_V;
		int token_root_ssl_output_file_O;
		int token_root_ssl_output_file_path_V;
		int token_root_ssl_output_file_path_S;
		int token_root_ssl_output_socket_V;
		int token_root_ssl_output_socket_O;
		int token_root_ssl_output_socket_port_V;
		int token_root_ssl_output_socket_port_N;	

		int token_root_sst_V;
		int token_root_sst_O;

		int token_root_sst_mode_V;
		int token_root_sst_mode_S;
		int token_root_sst_add_V;
		int token_root_sst_add_S;

		int token_root_sst_energy_V;
		int token_root_sst_energy_O;
		int token_root_sst_energy_active_V;
		int token_root_sst_energy_active_A;
		int token_root_sst_energy_active_e_V[SETTINGS_NGAUSSIANS];
		int token_root_sst_energy_active_e_O[SETTINGS_NGAUSSIANS];
		int token_root_sst_energy_active_e_weight_V[SETTINGS_NGAUSSIANS];
		int token_root_sst_energy_active_e_weight_N[SETTINGS_NGAUSSIANS];
		int token_root_sst_energy_active_e_mu_V[SETTINGS_NGAUSSIANS];
		int token_root_sst_energy_active_e_mu_N[SETTINGS_NGAUSSIANS];
		int token_root_sst_energy_active_e_sigma2_V[SETTINGS_NGAUSSIANS];
		int token_root_sst_energy_active_e_sigma2_N[SETTINGS_NGAUSSIANS];
		int token_root_sst_energy_inactive_V;
		int token_root_sst_energy_inactive_A;
		int token_root_sst_energy_inactive_e_V[SETTINGS_NGAUSSIANS];
		int token_root_sst_energy_inactive_e_O[SETTINGS_NGAUSSIANS];
		int token_root_sst_energy_inactive_e_weight_V[SETTINGS_NGAUSSIANS];
		int token_root_sst_energy_inactive_e_weight_N[SETTINGS_NGAUSSIANS];
		int token_root_sst_energy_inactive_e_mu_V[SETTINGS_NGAUSSIANS];
		int token_root_sst_energy_inactive_e_mu_N[SETTINGS_NGAUSSIANS];
		int token_root_sst_energy_inactive_e_sigma2_V[SETTINGS_NGAUSSIANS];
		int token_root_sst_energy_inactive_e_sigma2_N[SETTINGS_NGAUSSIANS];
		
		int token_root_sst_sigmaR2_V;
		int token_root_sst_sigmaR2_O;
		int token_root_sst_sigmaR2_prob_V;
		int token_root_sst_sigmaR2_prob_N;
		int token_root_sst_sigmaR2_active_V;
		int token_root_sst_sigmaR2_active_N;
		int token_root_sst_sigmaR2_target_V;
		int token_root_sst_sigmaR2_target_N;

		int token_root_sst_P_V;
		int token_root_sst_P_O;
		int token_root_sst_P_false_V;
		int token_root_sst_P_false_N;
		int token_root_sst_P_new_V;
		int token_root_sst_P_new_N;
		int token_root_sst_P_track_V;
		int token_root_sst_P_track_N;

		int token_root_sst_levels_V;
		int token_root_sst_levels_O;
		int token_root_sst_levels_new_V;
		int token_root_sst_levels_new_O;
		int token_root_sst_levels_new_theta_V;
		int token_root_sst_levels_new_theta_N;
		int token_root_sst_levels_prob_V;
		int token_root_sst_levels_prob_O;
		int token_root_sst_levels_prob_theta_V;
		int token_root_sst_levels_prob_theta_N;
		int token_root_sst_levels_prob_N_V;
		int token_root_sst_levels_prob_N_N;
		int token_root_sst_levels_inactive_V;
		int token_root_sst_levels_inactive_O;
		int token_root_sst_levels_inactive_theta_V;
		int token_root_sst_levels_inactive_theta_N;
		int token_root_sst_levels_inactive_Ns_V;
		int token_root_sst_levels_inactive_Ns_A;
		int token_root_sst_levels_inactive_Ns_e_V[SETTINGS_NLEVELS];
		int token_root_sst_levels_inactive_Ns_e_N[SETTINGS_NLEVELS];

		int token_root_sst_kalman_V;
		int token_root_sst_kalman_O;
		int token_root_sst_kalman_sigmaQ_V;
		int token_root_sst_kalman_sigmaQ_N;

		int token_root_sst_particle_V;
		int token_root_sst_particle_O;
		int token_root_sst_particle_nParticles_V;
		int token_root_sst_particle_nParticles_N;
		int token_root_sst_particle_stationary_V;
		int token_root_sst_particle_stationary_O;
		int token_root_sst_particle_stationary_alpha_V;
		int token_root_sst_particle_stationary_alpha_N;
		int token_root_sst_particle_stationary_beta_V;
		int token_root_sst_particle_stationary_beta_N;
		int token_root_sst_particle_stationary_ratio_V;
		int token_root_sst_particle_stationary_ratio_N;
		int token_root_sst_particle_velocity_V;
		int token_root_sst_particle_velocity_O;
		int token_root_sst_particle_velocity_alpha_V;
		int token_root_sst_particle_velocity_alpha_N;
		int token_root_sst_particle_velocity_beta_V;
		int token_root_sst_particle_velocity_beta_N;
		int token_root_sst_particle_velocity_ratio_V;
		int token_root_sst_particle_velocity_ratio_N;
		int token_root_sst_particle_acceleration_V;
		int token_root_sst_particle_acceleration_O;
		int token_root_sst_particle_acceleration_alpha_V;
		int token_root_sst_particle_acceleration_alpha_N;
		int token_root_sst_particle_acceleration_beta_V;
		int token_root_sst_particle_acceleration_beta_N;
		int token_root_sst_particle_acceleration_ratio_V;
		int token_root_sst_particle_acceleration_ratio_N;
		int token_root_sst_particle_Nmin_V;
		int token_root_sst_particle_Nmin_N;

		int token_root_sst_targets_V;
		int token_root_sst_targets_A;
		int token_root_sst_targets_e_V[SETTINGS_NTARGETS];
		int token_root_sst_targets_e_O[SETTINGS_NTARGETS];
		int token_root_sst_targets_e_tag_V[SETTINGS_NTARGETS];
		int token_root_sst_targets_e_tag_S[SETTINGS_NTARGETS];
		int token_root_sst_targets_e_x_V[SETTINGS_NTARGETS];
		int token_root_sst_targets_e_x_N[SETTINGS_NTARGETS];
		int token_root_sst_targets_e_y_V[SETTINGS_NTARGETS];
		int token_root_sst_targets_e_y_N[SETTINGS_NTARGETS];
		int token_root_sst_targets_e_z_V[SETTINGS_NTARGETS];
		int token_root_sst_targets_e_z_N[SETTINGS_NTARGETS];

		int token_root_sst_input_V;
		int token_root_sst_input_O;
		int token_root_sst_input_type_V;
		int token_root_sst_input_type_S;
		int token_root_sst_input_file_V;
		int token_root_sst_input_file_O;
		int token_root_sst_input_file_path_V;
		int token_root_sst_input_file_path_S;
		int token_root_sst_input_socket_V;
		int token_root_sst_input_socket_O;
		int token_root_sst_input_socket_port_V;
		int token_root_sst_input_socket_port_N;

		int token_root_sst_output_V;
		int token_root_sst_output_O;
		int token_root_sst_output_type_V;
		int token_root_sst_output_type_S;
		int token_root_sst_output_file_V;
		int token_root_sst_output_file_O;
		int token_root_sst_output_file_path_V;
		int token_root_sst_output_file_path_S;
		int token_root_sst_output_socket_V;
		int token_root_sst_output_socket_O;
		int token_root_sst_output_socket_port_V;
		int token_root_sst_output_socket_port_N;	

		int token_root_sss_V;
		int token_root_sss_O;

		int token_root_sss_offset_V;
		int token_root_sss_offset_N;

		int token_root_sss_separation_V;
		int token_root_sss_separation_O;

		int token_root_sss_separation_mode_V;
		int token_root_sss_separation_mode_S;
		int token_root_sss_separation_techniques_V;
		int token_root_sss_separation_techniques_O;
		int token_root_sss_separation_techniques_dds_V;
		int token_root_sss_separation_techniques_dds_O;
		int token_root_sss_separation_techniques_dgss_V;
		int token_root_sss_separation_techniques_dgss_O;
		int token_root_sss_separation_techniques_dgss_mu_V;
		int token_root_sss_separation_techniques_dgss_mu_N;
		int token_root_sss_separation_techniques_dgss_lambda_V;
		int token_root_sss_separation_techniques_dgss_lambda_N;
		int token_root_sss_separation_techniques_dmvdr_V;
		int token_root_sss_separation_techniques_dmvdr_O;
		int token_root_sss_separation_format_V;
		int token_root_sss_separation_format_O;
		int token_root_sss_separation_format_fS_V;
		int token_root_sss_separation_format_fS_N;
		int token_root_sss_separation_format_hopSize_V;
		int token_root_sss_separation_format_hopSize_N;
		int token_root_sss_separation_format_nBits_V;
		int token_root_sss_separation_format_nBits_N;	
		int token_root_sss_separation_output_V;
		int token_root_sss_separation_output_O;
		int token_root_sss_separation_output_type_V;
		int token_root_sss_separation_output_type_S;
		int token_root_sss_separation_output_file_V;
		int token_root_sss_separation_output_file_O;
		int token_root_sss_separation_output_file_path_V;
		int token_root_sss_separation_output_file_path_S;
		int token_root_sss_separation_output_socket_V;
		int token_root_sss_separation_output_socket_O;
		int token_root_sss_separation_output_socket_port_V;
		int token_root_sss_separation_output_socket_port_N;

		int token_root_sss_postfiltering_V;
		int token_root_sss_postfiltering_O;

		int token_root_sss_postfiltering_mode_V;
		int token_root_sss_postfiltering_mode_S;
		int token_root_sss_postfiltering_techniques_V;
		int token_root_sss_postfiltering_techniques_O;
		int token_root_sss_postfiltering_techniques_ms_V;
		int token_root_sss_postfiltering_techniques_ms_O;
		int token_root_sss_postfiltering_techniques_ms_alphaPmin_V;
		int token_root_sss_postfiltering_techniques_ms_alphaPmin_N;
		int token_root_sss_postfiltering_techniques_ms_eta_V;
		int token_root_sss_postfiltering_techniques_ms_eta_N;
		int token_root_sss_postfiltering_techniques_ms_alphaZ_V;
		int token_root_sss_postfiltering_techniques_ms_alphaZ_N;
		int token_root_sss_postfiltering_techniques_ms_thetaWin_V;
		int token_root_sss_postfiltering_techniques_ms_thetaWin_N;
		int token_root_sss_postfiltering_techniques_ms_alphaWin_V;
		int token_root_sss_postfiltering_techniques_ms_alphaWin_N;
		int token_root_sss_postfiltering_techniques_ms_maxAbsenceProb_V;
		int token_root_sss_postfiltering_techniques_ms_maxAbsenceProb_N;
		int token_root_sss_postfiltering_techniques_ms_Gmin_V;
		int token_root_sss_postfiltering_techniques_ms_Gmin_N;
		int token_root_sss_postfiltering_techniques_ms_winSizeLocal_V;
		int token_root_sss_postfiltering_techniques_ms_winSizeLocal_N;
		int token_root_sss_postfiltering_techniques_ms_winSizeGlobal_V;
		int token_root_sss_postfiltering_techniques_ms_winSizeGlobal_N;
		int token_root_sss_postfiltering_techniques_ms_winSizeFrame_V;
		int token_root_sss_postfiltering_techniques_ms_winSizeFrame_N;
		int token_root_sss_postfiltering_techniques_ss_V;
		int token_root_sss_postfiltering_techniques_ss_O;
		int token_root_sss_postfiltering_techniques_ss_Gmin_V;
		int token_root_sss_postfiltering_techniques_ss_Gmin_N;
		int token_root_sss_postfiltering_techniques_ss_Gmid_V;
		int token_root_sss_postfiltering_techniques_ss_Gmid_N;
		int token_root_sss_postfiltering_techniques_ss_Gslope_V;
		int token_root_sss_postfiltering_techniques_ss_Gslope_N;
		int token_root_sss_postfiltering_format_V;
		int token_root_sss_postfiltering_format_O;
		int token_root_sss_postfiltering_format_fS_V;
		int token_root_sss_postfiltering_format_fS_N;
		int token_root_sss_postfiltering_format_hopSize_V;
		int token_root_sss_postfiltering_format_hopSize_N;
		int token_root_sss_postfiltering_format_nBits_V;
		int token_root_sss_postfiltering_format_nBits_N;	
		int token_root_sss_postfiltering_output_V;
		int token_root_sss_postfiltering_output_O;
		int token_root_sss_postfiltering_output_type_V;
		int token_root_sss_postfiltering_output_type_S;
		int token_root_sss_postfiltering_output_file_V;
		int token_root_sss_postfiltering_output_file_O;
		int token_root_sss_postfiltering_output_file_path_V;
		int token_root_sss_postfiltering_output_file_path_S;
		int token_root_sss_postfiltering_output_socket_V;
		int token_root_sss_postfiltering_output_socket_O;
		int token_root_sss_postfiltering_output_socket_port_V;
		int token_root_sss_postfiltering_output_socket_port_N;

		unsigned int iChannel, nChannels;
		unsigned int iMic, nMics;
		unsigned int iSpatialFilter, nSpatialFilters;
		unsigned int iScan, nScans;
		unsigned int iGaussianActive, nGaussiansActive;
		unsigned int iGaussianInactive, nGaussiansInactive;
		unsigned int iLevel, nLevels;
		unsigned int iTarget, nTargets;

		// Allocate

		tokens = json_tokens_construct(nTokens);
		line = (char *) malloc(sizeof(char) * nBytesPerLine);
		string = (char *) malloc(sizeof(char) * nBytesPerString);

		// Load file in a string
		
		fp = fopen(file, "r");
		string[0] = 0x00;
		if (fp == NULL) { printf("Cannot open file %s\n", file); exit(EXIT_FAILURE); }
		while(feof(fp)==0) {
			line[0] = 0x00;
			line = fgets(line, nBytesPerLine, fp);
			strcat(string, line);
		}
		fclose(fp);
		
		// Parse
		
		json_tokens_clear(tokens);
		parseRtn = json_tokens_parse(tokens, string);
		if (parseRtn == -1) { printf("JSON file has invalid format\n"); exit(EXIT_FAILURE); }

		// Reference each token
		
		token_root_O = json_tokens_getFromValue(tokens, string, -1);

		token_root_raw_V = json_tokens_getFromObject(tokens, string, token_root_O, "raw");
		token_root_raw_O = json_tokens_getFromValue(tokens, string, token_root_raw_V);

		token_root_raw_format_V = json_tokens_getFromObject(tokens, string, token_root_raw_O, "format");
		token_root_raw_format_O = json_tokens_getFromValue(tokens, string, token_root_raw_format_V);
		token_root_raw_format_fS_V = json_tokens_getFromObject(tokens, string, token_root_raw_format_O, "fS");
		token_root_raw_format_fS_N = json_tokens_getFromValue(tokens, string, token_root_raw_format_fS_V);
		token_root_raw_format_hopSize_V = json_tokens_getFromObject(tokens, string, token_root_raw_format_O, "hopSize");
		token_root_raw_format_hopSize_N = json_tokens_getFromValue(tokens, string, token_root_raw_format_hopSize_V);
		token_root_raw_format_nBits_V = json_tokens_getFromObject(tokens, string, token_root_raw_format_O, "nBits");
		token_root_raw_format_nBits_N = json_tokens_getFromValue(tokens, string, token_root_raw_format_nBits_V);

		token_root_raw_nChannels_V = json_tokens_getFromObject(tokens, string, token_root_raw_O, "nChannels");
		token_root_raw_nChannels_N = json_tokens_getFromValue(tokens, string, token_root_raw_nChannels_V);

		token_root_raw_input_V = json_tokens_getFromObject(tokens, string, token_root_raw_O, "input");
		token_root_raw_input_O = json_tokens_getFromValue(tokens, string, token_root_raw_input_V);
		token_root_raw_input_type_V = json_tokens_getFromObject(tokens, string, token_root_raw_input_O, "type");
		token_root_raw_input_type_S = json_tokens_getFromValue(tokens, string, token_root_raw_input_type_V);
		token_root_raw_input_file_V = json_tokens_getFromObject(tokens, string, token_root_raw_input_O, "file");
		token_root_raw_input_file_O = json_tokens_getFromValue(tokens, string, token_root_raw_input_file_V);
		token_root_raw_input_file_path_V = json_tokens_getFromObject(tokens, string, token_root_raw_input_file_O, "path");
		token_root_raw_input_file_path_S = json_tokens_getFromValue(tokens, string, token_root_raw_input_file_path_V);
		token_root_raw_input_socket_V = json_tokens_getFromObject(tokens, string, token_root_raw_input_O, "socket");
		token_root_raw_input_socket_O = json_tokens_getFromValue(tokens, string, token_root_raw_input_socket_V);
		token_root_raw_input_socket_port_V = json_tokens_getFromObject(tokens, string, token_root_raw_input_socket_O, "port");
		token_root_raw_input_socket_port_N = json_tokens_getFromValue(tokens, string, token_root_raw_input_socket_port_V);
		token_root_raw_input_soundcard_V = json_tokens_getFromObject(tokens, string, token_root_raw_input_O, "soundcard");
		token_root_raw_input_soundcard_O = json_tokens_getFromValue(tokens, string, token_root_raw_input_soundcard_V);
		token_root_raw_input_soundcard_device_V = json_tokens_getFromObject(tokens, string, token_root_raw_input_soundcard_O, "device");
		token_root_raw_input_soundcard_device_S = json_tokens_getFromValue(tokens, string, token_root_raw_input_soundcard_device_V);		

		token_root_raw_output_V = json_tokens_getFromObject(tokens, string, token_root_raw_O, "output");
		token_root_raw_output_O = json_tokens_getFromValue(tokens, string, token_root_raw_output_V);
		token_root_raw_output_type_V = json_tokens_getFromObject(tokens, string, token_root_raw_output_O, "type");
		token_root_raw_output_type_S = json_tokens_getFromValue(tokens, string, token_root_raw_output_type_V);
		token_root_raw_output_file_V = json_tokens_getFromObject(tokens, string, token_root_raw_output_O, "file");
		token_root_raw_output_file_O = json_tokens_getFromValue(tokens, string, token_root_raw_output_file_V);
		token_root_raw_output_file_path_V = json_tokens_getFromObject(tokens, string, token_root_raw_output_file_O, "path");
		token_root_raw_output_file_path_S = json_tokens_getFromValue(tokens, string, token_root_raw_output_file_path_V);
		token_root_raw_output_socket_V = json_tokens_getFromObject(tokens, string, token_root_raw_output_O, "socket");
		token_root_raw_output_socket_O = json_tokens_getFromValue(tokens, string, token_root_raw_output_socket_V);
		token_root_raw_output_socket_port_V = json_tokens_getFromObject(tokens, string, token_root_raw_output_socket_O, "port");
		token_root_raw_output_socket_port_N = json_tokens_getFromValue(tokens, string, token_root_raw_output_socket_port_V);

		token_root_mapping_V = json_tokens_getFromObject(tokens, string, token_root_O, "mapping");
		token_root_mapping_O = json_tokens_getFromValue(tokens, string, token_root_mapping_V);

		token_root_mapping_map_V = json_tokens_getFromObject(tokens, string, token_root_mapping_O, "map");
		token_root_mapping_map_A = json_tokens_getFromValue(tokens, string, token_root_mapping_map_V);
		
		nChannels = json_tokens_count(tokens, string, token_root_mapping_map_A);

		for (iChannel = 0; iChannel < nChannels; iChannel++) {

			token_root_mapping_map_e_V[iChannel] = json_tokens_getFromArray(tokens, string, token_root_mapping_map_A, iChannel);
			token_root_mapping_map_e_N[iChannel] = json_tokens_getFromValue(tokens, string, token_root_mapping_map_e_V[iChannel]);

		}

		token_root_general_V = json_tokens_getFromObject(tokens, string, token_root_O, "general");
		token_root_general_O = json_tokens_getFromValue(tokens, string, token_root_general_V);

		token_root_general_epsilon_V = json_tokens_getFromObject(tokens, string, token_root_general_O, "epsilon");
		token_root_general_epsilon_N = json_tokens_getFromValue(tokens, string, token_root_general_epsilon_V);
		token_root_general_size_V = json_tokens_getFromObject(tokens, string, token_root_general_O, "size");
		token_root_general_size_O = json_tokens_getFromValue(tokens, string, token_root_general_size_V);
		token_root_general_size_hopSize_V = json_tokens_getFromObject(tokens, string, token_root_general_size_O, "hopSize");
		token_root_general_size_hopSize_N = json_tokens_getFromValue(tokens, string, token_root_general_size_hopSize_V);
		token_root_general_size_frameSize_V = json_tokens_getFromObject(tokens, string, token_root_general_size_O, "frameSize");
		token_root_general_size_frameSize_N = json_tokens_getFromValue(tokens, string, token_root_general_size_frameSize_V);
		token_root_general_samplerate_V = json_tokens_getFromObject(tokens, string, token_root_general_O, "samplerate");
		token_root_general_samplerate_O = json_tokens_getFromValue(tokens, string, token_root_general_samplerate_V);
		token_root_general_samplerate_mu_V = json_tokens_getFromObject(tokens, string, token_root_general_samplerate_O, "mu");
		token_root_general_samplerate_mu_N = json_tokens_getFromValue(tokens, string, token_root_general_samplerate_mu_V);
		token_root_general_samplerate_sigma2_V = json_tokens_getFromObject(tokens, string, token_root_general_samplerate_O, "sigma2");
		token_root_general_samplerate_sigma2_N = json_tokens_getFromValue(tokens, string, token_root_general_samplerate_sigma2_V);
		token_root_general_speedofsound_V = json_tokens_getFromObject(tokens, string, token_root_general_O, "speedofsound");
		token_root_general_speedofsound_O = json_tokens_getFromValue(tokens, string, token_root_general_speedofsound_V);
		token_root_general_speedofsound_mu_V = json_tokens_getFromObject(tokens, string, token_root_general_speedofsound_O, "mu");
		token_root_general_speedofsound_mu_N = json_tokens_getFromValue(tokens, string, token_root_general_speedofsound_mu_V);
		token_root_general_speedofsound_sigma2_V = json_tokens_getFromObject(tokens, string, token_root_general_speedofsound_O, "sigma2");
		token_root_general_speedofsound_sigma2_N = json_tokens_getFromValue(tokens, string, token_root_general_speedofsound_sigma2_V);

		token_root_general_mics_V = json_tokens_getFromObject(tokens, string, token_root_general_O, "mics");
		token_root_general_mics_A = json_tokens_getFromValue(tokens, string, token_root_general_mics_V);
		
		nMics = json_tokens_count(tokens, string, token_root_general_mics_A);

		for (iMic = 0; iMic < nMics; iMic++) {

			token_root_general_mics_e_V[iMic] = json_tokens_getFromArray(tokens, string, token_root_general_mics_A, iMic);
			token_root_general_mics_e_O[iMic] = json_tokens_getFromValue(tokens, string, token_root_general_mics_e_V[iMic]);

			token_root_general_mics_e_mus_V[iMic] = json_tokens_getFromObject(tokens, string, token_root_general_mics_e_O[iMic], "mu");
			token_root_general_mics_e_mus_A[iMic] = json_tokens_getFromValue(tokens, string, token_root_general_mics_e_mus_V[iMic]);

			token_root_general_mics_e_mus_0_V[iMic] = json_tokens_getFromArray(tokens, string, token_root_general_mics_e_mus_A[iMic], 0);
			token_root_general_mics_e_mus_0_N[iMic] = json_tokens_getFromValue(tokens, string, token_root_general_mics_e_mus_0_V[iMic]);
			token_root_general_mics_e_mus_1_V[iMic] = json_tokens_getFromArray(tokens, string, token_root_general_mics_e_mus_A[iMic], 1);
			token_root_general_mics_e_mus_1_N[iMic] = json_tokens_getFromValue(tokens, string, token_root_general_mics_e_mus_1_V[iMic]);
			token_root_general_mics_e_mus_2_V[iMic] = json_tokens_getFromArray(tokens, string, token_root_general_mics_e_mus_A[iMic], 2);
			token_root_general_mics_e_mus_2_N[iMic] = json_tokens_getFromValue(tokens, string, token_root_general_mics_e_mus_2_V[iMic]);

			token_root_general_mics_e_sigma2s_V[iMic] = json_tokens_getFromObject(tokens, string, token_root_general_mics_e_O[iMic], "sigma2");
			token_root_general_mics_e_sigma2s_A[iMic] = json_tokens_getFromValue(tokens, string, token_root_general_mics_e_sigma2s_V[iMic]);

			token_root_general_mics_e_sigma2s_0_V[iMic] = json_tokens_getFromArray(tokens, string, token_root_general_mics_e_sigma2s_A[iMic], 0);
			token_root_general_mics_e_sigma2s_0_N[iMic] = json_tokens_getFromValue(tokens, string, token_root_general_mics_e_sigma2s_0_V[iMic]);
			token_root_general_mics_e_sigma2s_1_V[iMic] = json_tokens_getFromArray(tokens, string, token_root_general_mics_e_sigma2s_A[iMic], 1);
			token_root_general_mics_e_sigma2s_1_N[iMic] = json_tokens_getFromValue(tokens, string, token_root_general_mics_e_sigma2s_1_V[iMic]);
			token_root_general_mics_e_sigma2s_2_V[iMic] = json_tokens_getFromArray(tokens, string, token_root_general_mics_e_sigma2s_A[iMic], 2);
			token_root_general_mics_e_sigma2s_2_N[iMic] = json_tokens_getFromValue(tokens, string, token_root_general_mics_e_sigma2s_2_V[iMic]);
			token_root_general_mics_e_sigma2s_3_V[iMic] = json_tokens_getFromArray(tokens, string, token_root_general_mics_e_sigma2s_A[iMic], 3);
			token_root_general_mics_e_sigma2s_3_N[iMic] = json_tokens_getFromValue(tokens, string, token_root_general_mics_e_sigma2s_3_V[iMic]);
			token_root_general_mics_e_sigma2s_4_V[iMic] = json_tokens_getFromArray(tokens, string, token_root_general_mics_e_sigma2s_A[iMic], 4);
			token_root_general_mics_e_sigma2s_4_N[iMic] = json_tokens_getFromValue(tokens, string, token_root_general_mics_e_sigma2s_4_V[iMic]);
			token_root_general_mics_e_sigma2s_5_V[iMic] = json_tokens_getFromArray(tokens, string, token_root_general_mics_e_sigma2s_A[iMic], 5);
			token_root_general_mics_e_sigma2s_5_N[iMic] = json_tokens_getFromValue(tokens, string, token_root_general_mics_e_sigma2s_5_V[iMic]);
			token_root_general_mics_e_sigma2s_6_V[iMic] = json_tokens_getFromArray(tokens, string, token_root_general_mics_e_sigma2s_A[iMic], 6);
			token_root_general_mics_e_sigma2s_6_N[iMic] = json_tokens_getFromValue(tokens, string, token_root_general_mics_e_sigma2s_6_V[iMic]);
			token_root_general_mics_e_sigma2s_7_V[iMic] = json_tokens_getFromArray(tokens, string, token_root_general_mics_e_sigma2s_A[iMic], 7);
			token_root_general_mics_e_sigma2s_7_N[iMic] = json_tokens_getFromValue(tokens, string, token_root_general_mics_e_sigma2s_7_V[iMic]);
			token_root_general_mics_e_sigma2s_8_V[iMic] = json_tokens_getFromArray(tokens, string, token_root_general_mics_e_sigma2s_A[iMic], 8);
			token_root_general_mics_e_sigma2s_8_N[iMic] = json_tokens_getFromValue(tokens, string, token_root_general_mics_e_sigma2s_8_V[iMic]);

			token_root_general_mics_e_directions_V[iMic] = json_tokens_getFromObject(tokens, string, token_root_general_mics_e_O[iMic], "direction");
			token_root_general_mics_e_directions_A[iMic] = json_tokens_getFromValue(tokens, string, token_root_general_mics_e_directions_V[iMic]);

			token_root_general_mics_e_directions_0_V[iMic] = json_tokens_getFromArray(tokens, string, token_root_general_mics_e_directions_A[iMic], 0);
			token_root_general_mics_e_directions_0_N[iMic] = json_tokens_getFromValue(tokens, string, token_root_general_mics_e_directions_0_V[iMic]);
			token_root_general_mics_e_directions_1_V[iMic] = json_tokens_getFromArray(tokens, string, token_root_general_mics_e_directions_A[iMic], 1);
			token_root_general_mics_e_directions_1_N[iMic] = json_tokens_getFromValue(tokens, string, token_root_general_mics_e_directions_1_V[iMic]);
			token_root_general_mics_e_directions_2_V[iMic] = json_tokens_getFromArray(tokens, string, token_root_general_mics_e_directions_A[iMic], 2);
			token_root_general_mics_e_directions_2_N[iMic] = json_tokens_getFromValue(tokens, string, token_root_general_mics_e_directions_2_V[iMic]);

			token_root_general_mics_e_angles_V[iMic] = json_tokens_getFromObject(tokens, string, token_root_general_mics_e_O[iMic], "angle");
			token_root_general_mics_e_angles_A[iMic] = json_tokens_getFromValue(tokens, string, token_root_general_mics_e_angles_V[iMic]);

			token_root_general_mics_e_angles_0_V[iMic] = json_tokens_getFromArray(tokens, string, token_root_general_mics_e_angles_A[iMic], 0);
			token_root_general_mics_e_angles_0_N[iMic] = json_tokens_getFromValue(tokens, string, token_root_general_mics_e_angles_0_V[iMic]);
			token_root_general_mics_e_angles_1_V[iMic] = json_tokens_getFromArray(tokens, string, token_root_general_mics_e_angles_A[iMic], 1);
			token_root_general_mics_e_angles_1_N[iMic] = json_tokens_getFromValue(tokens, string, token_root_general_mics_e_angles_1_V[iMic]);

		}

		token_root_general_spatialfilters_V = json_tokens_getFromObject(tokens, string, token_root_general_O, "spatialfilters");
		token_root_general_spatialfilters_A = json_tokens_getFromValue(tokens, string, token_root_general_spatialfilters_V);
		
		nSpatialFilters = json_tokens_count(tokens, string, token_root_general_spatialfilters_A);

		for (iSpatialFilter = 0; iSpatialFilter < nSpatialFilters; iSpatialFilter++) {

			token_root_general_spatialfilters_e_V[iSpatialFilter] = json_tokens_getFromArray(tokens, string, token_root_general_spatialfilters_A, iSpatialFilter);
			token_root_general_spatialfilters_e_O[iSpatialFilter] = json_tokens_getFromValue(tokens, string, token_root_general_spatialfilters_e_V[iSpatialFilter]);

			token_root_general_spatialfilters_e_directions_V[iSpatialFilter] = json_tokens_getFromObject(tokens, string, token_root_general_spatialfilters_e_O[iSpatialFilter], "directions");
			token_root_general_spatialfilters_e_directions_A[iSpatialFilter] = json_tokens_getFromValue(tokens, string, token_root_general_spatialfilters_e_directions_V[iSpatialFilter]);

			token_root_general_spatialfilters_e_directions_0_V[iSpatialFilter] = json_tokens_getFromArray(tokens, string, token_root_general_spatialfilters_e_directions_A[iSpatialFilter], 0);
			token_root_general_spatialfilters_e_directions_0_N[iSpatialFilter] = json_tokens_getFromValue(tokens, string, token_root_general_spatialfilters_e_directions_0_V[iSpatialFilter]);
			token_root_general_spatialfilters_e_directions_1_V[iSpatialFilter] = json_tokens_getFromArray(tokens, string, token_root_general_spatialfilters_e_directions_A[iSpatialFilter], 1);
			token_root_general_spatialfilters_e_directions_1_N[iSpatialFilter] = json_tokens_getFromValue(tokens, string, token_root_general_spatialfilters_e_directions_1_V[iSpatialFilter]);
			token_root_general_spatialfilters_e_directions_2_V[iSpatialFilter] = json_tokens_getFromArray(tokens, string, token_root_general_spatialfilters_e_directions_A[iSpatialFilter], 2);
			token_root_general_spatialfilters_e_directions_2_N[iSpatialFilter] = json_tokens_getFromValue(tokens, string, token_root_general_spatialfilters_e_directions_2_V[iSpatialFilter]);

			token_root_general_spatialfilters_e_angles_V[iSpatialFilter] = json_tokens_getFromObject(tokens, string, token_root_general_spatialfilters_e_O[iSpatialFilter], "angles");
			token_root_general_spatialfilters_e_angles_A[iSpatialFilter] = json_tokens_getFromValue(tokens, string, token_root_general_spatialfilters_e_angles_V[iSpatialFilter]);

			token_root_general_spatialfilters_e_angles_0_V[iSpatialFilter] = json_tokens_getFromArray(tokens, string, token_root_general_spatialfilters_e_angles_A[iSpatialFilter], 0);
			token_root_general_spatialfilters_e_angles_0_N[iSpatialFilter] = json_tokens_getFromValue(tokens, string, token_root_general_spatialfilters_e_angles_0_V[iSpatialFilter]);
			token_root_general_spatialfilters_e_angles_1_V[iSpatialFilter] = json_tokens_getFromArray(tokens, string, token_root_general_spatialfilters_e_angles_A[iSpatialFilter], 1);
			token_root_general_spatialfilters_e_angles_1_N[iSpatialFilter] = json_tokens_getFromValue(tokens, string, token_root_general_spatialfilters_e_angles_1_V[iSpatialFilter]);

		}

		token_root_general_nthetas_V = json_tokens_getFromObject(tokens, string, token_root_general_O, "nThetas");
		token_root_general_nthetas_N = json_tokens_getFromValue(tokens, string, token_root_general_nthetas_V);
		token_root_general_gainmin_V = json_tokens_getFromObject(tokens, string, token_root_general_O, "gainMin");
		token_root_general_gainmin_N = json_tokens_getFromValue(tokens, string, token_root_general_gainmin_V);

		token_root_sne_V = json_tokens_getFromObject(tokens, string, token_root_O, "sne");
		token_root_sne_O = json_tokens_getFromValue(tokens, string, token_root_sne_V);

		token_root_sne_b_V = json_tokens_getFromObject(tokens, string, token_root_sne_O, "b");
		token_root_sne_b_N = json_tokens_getFromValue(tokens, string, token_root_sne_b_V);
		token_root_sne_alphaS_V = json_tokens_getFromObject(tokens, string, token_root_sne_O, "alphaS");
		token_root_sne_alphaS_N = json_tokens_getFromValue(tokens, string, token_root_sne_alphaS_V);
		token_root_sne_L_V = json_tokens_getFromObject(tokens, string, token_root_sne_O, "L");
		token_root_sne_L_N = json_tokens_getFromValue(tokens, string, token_root_sne_L_V);
		token_root_sne_delta_V = json_tokens_getFromObject(tokens, string, token_root_sne_O, "delta");
		token_root_sne_delta_N = json_tokens_getFromValue(tokens, string, token_root_sne_delta_V);
		token_root_sne_alphaD_V = json_tokens_getFromObject(tokens, string, token_root_sne_O, "alphaD");
		token_root_sne_alphaD_N = json_tokens_getFromValue(tokens, string, token_root_sne_alphaD_V);

		token_root_ssl_V = json_tokens_getFromObject(tokens, string, token_root_O, "ssl");
		token_root_ssl_O = json_tokens_getFromValue(tokens, string, token_root_ssl_V);

		token_root_ssl_nPots_V = json_tokens_getFromObject(tokens, string, token_root_ssl_O, "nPots");
		token_root_ssl_nPots_N = json_tokens_getFromValue(tokens, string, token_root_ssl_nPots_V);
		token_root_ssl_nMatches_V = json_tokens_getFromObject(tokens, string, token_root_ssl_O, "nMatches");
		token_root_ssl_nMatches_N = json_tokens_getFromValue(tokens, string, token_root_ssl_nMatches_V);
		token_root_ssl_probMin_V = json_tokens_getFromObject(tokens, string, token_root_ssl_O, "probMin");
		token_root_ssl_probMin_N = json_tokens_getFromValue(tokens, string, token_root_ssl_probMin_V);
		token_root_ssl_nRefinedLevels_V = json_tokens_getFromObject(tokens, string, token_root_ssl_O, "nRefinedLevels");
		token_root_ssl_nRefinedLevels_N = json_tokens_getFromValue(tokens, string, token_root_ssl_nRefinedLevels_V);
		token_root_ssl_interpRate_V = json_tokens_getFromObject(tokens, string, token_root_ssl_O, "interpRate");
		token_root_ssl_interpRate_N = json_tokens_getFromValue(tokens, string, token_root_ssl_interpRate_V);

		token_root_ssl_scans_V = json_tokens_getFromObject(tokens, string, token_root_ssl_O, "scans");
		token_root_ssl_scans_A = json_tokens_getFromValue(tokens, string, token_root_ssl_scans_V);

		nScans = json_tokens_count(tokens, string, token_root_ssl_scans_A);

		for (iScan = 0; iScan < nScans; iScan++) {

			token_root_ssl_scans_e_V[iScan] = json_tokens_getFromArray(tokens, string, token_root_ssl_scans_A, iScan);
			token_root_ssl_scans_e_O[iScan] = json_tokens_getFromValue(tokens, string, token_root_ssl_scans_e_V[iScan]);

			token_root_ssl_scans_e_level_V[iScan] = json_tokens_getFromObject(tokens, string, token_root_ssl_scans_e_O[iScan], "level");
			token_root_ssl_scans_e_level_N[iScan] = json_tokens_getFromValue(tokens, string, token_root_ssl_scans_e_level_V[iScan]);
			token_root_ssl_scans_e_delta_V[iScan] = json_tokens_getFromObject(tokens, string, token_root_ssl_scans_e_O[iScan], "delta");
			token_root_ssl_scans_e_delta_N[iScan] = json_tokens_getFromValue(tokens, string, token_root_ssl_scans_e_delta_V[iScan]);

		}

		token_root_ssl_output_V = json_tokens_getFromObject(tokens, string, token_root_ssl_O, "output");
		token_root_ssl_output_O = json_tokens_getFromValue(tokens, string, token_root_ssl_output_V);
		token_root_ssl_output_type_V = json_tokens_getFromObject(tokens, string, token_root_ssl_output_O, "type");
		token_root_ssl_output_type_S = json_tokens_getFromValue(tokens, string, token_root_ssl_output_type_V);
		token_root_ssl_output_file_V = json_tokens_getFromObject(tokens, string, token_root_ssl_output_O, "file");
		token_root_ssl_output_file_O = json_tokens_getFromValue(tokens, string, token_root_ssl_output_file_V);
		token_root_ssl_output_file_path_V = json_tokens_getFromObject(tokens, string, token_root_ssl_output_file_O, "path");
		token_root_ssl_output_file_path_S = json_tokens_getFromValue(tokens, string, token_root_ssl_output_file_path_V);
		token_root_ssl_output_socket_V = json_tokens_getFromObject(tokens, string, token_root_ssl_output_O, "socket");
		token_root_ssl_output_socket_O = json_tokens_getFromValue(tokens, string, token_root_ssl_output_socket_V);
		token_root_ssl_output_socket_port_V = json_tokens_getFromObject(tokens, string, token_root_ssl_output_socket_O, "port");
		token_root_ssl_output_socket_port_N = json_tokens_getFromValue(tokens, string, token_root_ssl_output_socket_port_V);		

		token_root_sst_V = json_tokens_getFromObject(tokens, string, token_root_O, "sst");
		token_root_sst_O = json_tokens_getFromValue(tokens, string, token_root_sst_V);

		token_root_sst_mode_V = json_tokens_getFromObject(tokens, string, token_root_sst_O, "mode");
		token_root_sst_mode_S = json_tokens_getFromValue(tokens, string, token_root_sst_mode_V);
		token_root_sst_add_V = json_tokens_getFromObject(tokens, string, token_root_sst_O, "add");
		token_root_sst_add_S = json_tokens_getFromValue(tokens, string, token_root_sst_add_V);

		token_root_sst_energy_V = json_tokens_getFromObject(tokens, string, token_root_sst_O, "energy");
		token_root_sst_energy_O = json_tokens_getFromValue(tokens, string, token_root_sst_energy_V);
		token_root_sst_energy_active_V = json_tokens_getFromObject(tokens, string, token_root_sst_energy_O, "active");
		token_root_sst_energy_active_A = json_tokens_getFromValue(tokens, string, token_root_sst_energy_active_V);
		token_root_sst_energy_inactive_V = json_tokens_getFromObject(tokens, string, token_root_sst_energy_O, "inactive");
		token_root_sst_energy_inactive_A = json_tokens_getFromValue(tokens, string, token_root_sst_energy_inactive_V);

		nGaussiansActive = json_tokens_count(tokens, string, token_root_sst_energy_active_A);

		for (iGaussianActive = 0; iGaussianActive < nGaussiansActive; iGaussianActive++) {

			token_root_sst_energy_active_e_V[iGaussianActive] = json_tokens_getFromArray(tokens, string, token_root_sst_energy_active_A, iGaussianActive);
			token_root_sst_energy_active_e_O[iGaussianActive] = json_tokens_getFromValue(tokens, string, token_root_sst_energy_active_e_V[iGaussianActive]);
			token_root_sst_energy_active_e_weight_V[iGaussianActive] = json_tokens_getFromObject(tokens, string, token_root_sst_energy_active_e_O[iGaussianActive], "weight");
			token_root_sst_energy_active_e_weight_N[iGaussianActive] = json_tokens_getFromValue(tokens, string, token_root_sst_energy_active_e_weight_V[iGaussianActive]);
			token_root_sst_energy_active_e_mu_V[iGaussianActive] = json_tokens_getFromObject(tokens, string, token_root_sst_energy_active_e_O[iGaussianActive], "mu");
			token_root_sst_energy_active_e_mu_N[iGaussianActive] = json_tokens_getFromValue(tokens, string, token_root_sst_energy_active_e_mu_V[iGaussianActive]);
			token_root_sst_energy_active_e_sigma2_V[iGaussianActive] = json_tokens_getFromObject(tokens, string, token_root_sst_energy_active_e_O[iGaussianActive], "sigma2");
			token_root_sst_energy_active_e_sigma2_N[iGaussianActive] = json_tokens_getFromValue(tokens, string, token_root_sst_energy_active_e_sigma2_V[iGaussianActive]);

		}

		nGaussiansInactive = json_tokens_count(tokens, string, token_root_sst_energy_inactive_A);

		for (iGaussianInactive = 0; iGaussianInactive < nGaussiansInactive; iGaussianInactive++) {

			token_root_sst_energy_inactive_e_V[iGaussianInactive] = json_tokens_getFromArray(tokens, string, token_root_sst_energy_inactive_A, iGaussianInactive);
			token_root_sst_energy_inactive_e_O[iGaussianInactive] = json_tokens_getFromValue(tokens, string, token_root_sst_energy_inactive_e_V[iGaussianInactive]);
			token_root_sst_energy_inactive_e_weight_V[iGaussianInactive] = json_tokens_getFromObject(tokens, string, token_root_sst_energy_inactive_e_O[iGaussianInactive], "weight");
			token_root_sst_energy_inactive_e_weight_N[iGaussianInactive] = json_tokens_getFromValue(tokens, string, token_root_sst_energy_inactive_e_weight_V[iGaussianInactive]);
			token_root_sst_energy_inactive_e_mu_V[iGaussianInactive] = json_tokens_getFromObject(tokens, string, token_root_sst_energy_inactive_e_O[iGaussianInactive], "mu");
			token_root_sst_energy_inactive_e_mu_N[iGaussianInactive] = json_tokens_getFromValue(tokens, string, token_root_sst_energy_inactive_e_mu_V[iGaussianInactive]);
			token_root_sst_energy_inactive_e_sigma2_V[iGaussianInactive] = json_tokens_getFromObject(tokens, string, token_root_sst_energy_inactive_e_O[iGaussianInactive], "sigma2");
			token_root_sst_energy_inactive_e_sigma2_N[iGaussianInactive] = json_tokens_getFromValue(tokens, string, token_root_sst_energy_inactive_e_sigma2_V[iGaussianInactive]);

		}

		token_root_sst_sigmaR2_V = json_tokens_getFromObject(tokens, string, token_root_sst_O, "sigmaR2");
		token_root_sst_sigmaR2_O = json_tokens_getFromValue(tokens, string, token_root_sst_sigmaR2_V);
		token_root_sst_sigmaR2_prob_V = json_tokens_getFromObject(tokens, string, token_root_sst_sigmaR2_O, "prob");
		token_root_sst_sigmaR2_prob_N = json_tokens_getFromValue(tokens, string, token_root_sst_sigmaR2_prob_V);
		token_root_sst_sigmaR2_active_V = json_tokens_getFromObject(tokens, string, token_root_sst_sigmaR2_O, "active");
		token_root_sst_sigmaR2_active_N = json_tokens_getFromValue(tokens, string, token_root_sst_sigmaR2_active_V);
		token_root_sst_sigmaR2_target_V = json_tokens_getFromObject(tokens, string, token_root_sst_sigmaR2_O, "target");
		token_root_sst_sigmaR2_target_N = json_tokens_getFromValue(tokens, string, token_root_sst_sigmaR2_target_V);

		token_root_sst_P_V = json_tokens_getFromObject(tokens, string, token_root_sst_O, "P");
		token_root_sst_P_O = json_tokens_getFromValue(tokens, string, token_root_sst_P_V);
		token_root_sst_P_false_V = json_tokens_getFromObject(tokens, string, token_root_sst_P_O, "false");
		token_root_sst_P_false_N = json_tokens_getFromValue(tokens, string, token_root_sst_P_false_V);
		token_root_sst_P_new_V = json_tokens_getFromObject(tokens, string, token_root_sst_P_O, "new");
		token_root_sst_P_new_N = json_tokens_getFromValue(tokens, string, token_root_sst_P_new_V);
		token_root_sst_P_track_V = json_tokens_getFromObject(tokens, string, token_root_sst_P_O, "track");
		token_root_sst_P_track_N = json_tokens_getFromValue(tokens, string, token_root_sst_P_track_V);

		token_root_sst_levels_V = json_tokens_getFromObject(tokens, string, token_root_sst_O, "levels");
		token_root_sst_levels_O = json_tokens_getFromValue(tokens, string, token_root_sst_levels_V);
		token_root_sst_levels_new_V = json_tokens_getFromObject(tokens, string, token_root_sst_levels_O, "new");
		token_root_sst_levels_new_O = json_tokens_getFromValue(tokens, string, token_root_sst_levels_new_V);
		token_root_sst_levels_new_theta_V = json_tokens_getFromObject(tokens, string, token_root_sst_levels_new_O, "theta");
		token_root_sst_levels_new_theta_N = json_tokens_getFromValue(tokens, string, token_root_sst_levels_new_theta_V);
		token_root_sst_levels_prob_V = json_tokens_getFromObject(tokens, string, token_root_sst_levels_O, "prob");
		token_root_sst_levels_prob_O = json_tokens_getFromValue(tokens, string, token_root_sst_levels_prob_V);
		token_root_sst_levels_prob_theta_V = json_tokens_getFromObject(tokens, string, token_root_sst_levels_prob_O, "theta");
		token_root_sst_levels_prob_theta_N = json_tokens_getFromValue(tokens, string, token_root_sst_levels_prob_theta_V);
		token_root_sst_levels_prob_N_V = json_tokens_getFromObject(tokens, string, token_root_sst_levels_prob_O, "N");
		token_root_sst_levels_prob_N_N = json_tokens_getFromValue(tokens, string, token_root_sst_levels_prob_N_V);
		token_root_sst_levels_inactive_V = json_tokens_getFromObject(tokens, string, token_root_sst_levels_O, "inactive");
		token_root_sst_levels_inactive_O = json_tokens_getFromValue(tokens, string, token_root_sst_levels_inactive_V);
		token_root_sst_levels_inactive_theta_V = json_tokens_getFromObject(tokens, string, token_root_sst_levels_inactive_O, "theta");
		token_root_sst_levels_inactive_theta_N = json_tokens_getFromValue(tokens, string, token_root_sst_levels_inactive_theta_V);
		token_root_sst_levels_inactive_Ns_V = json_tokens_getFromObject(tokens, string, token_root_sst_levels_inactive_O, "N");
		token_root_sst_levels_inactive_Ns_A = json_tokens_getFromValue(tokens, string, token_root_sst_levels_inactive_Ns_V);

		nLevels = json_tokens_count(tokens, string, token_root_sst_levels_inactive_Ns_A);

		for (iLevel = 0; iLevel < nLevels; iLevel++) {

			token_root_sst_levels_inactive_Ns_e_V[iLevel] = json_tokens_getFromArray(tokens, string, token_root_sst_levels_inactive_Ns_A, iLevel);
			token_root_sst_levels_inactive_Ns_e_N[iLevel] = json_tokens_getFromValue(tokens, string, token_root_sst_levels_inactive_Ns_e_V[iLevel]);

		}

		token_root_sst_kalman_V = json_tokens_getFromObject(tokens, string, token_root_sst_O, "kalman");
		token_root_sst_kalman_O = json_tokens_getFromValue(tokens, string, token_root_sst_kalman_V);
		token_root_sst_kalman_sigmaQ_V = json_tokens_getFromObject(tokens, string, token_root_sst_kalman_O, "sigmaQ");
		token_root_sst_kalman_sigmaQ_N = json_tokens_getFromValue(tokens, string, token_root_sst_kalman_sigmaQ_V);

		token_root_sst_particle_V = json_tokens_getFromObject(tokens, string, token_root_sst_O, "particle");
		token_root_sst_particle_O = json_tokens_getFromValue(tokens, string, token_root_sst_particle_V);
		token_root_sst_particle_nParticles_V = json_tokens_getFromObject(tokens, string, token_root_sst_particle_O, "nParticles");
		token_root_sst_particle_nParticles_N = json_tokens_getFromValue(tokens, string, token_root_sst_particle_nParticles_V);

		token_root_sst_particle_stationary_V = json_tokens_getFromObject(tokens, string, token_root_sst_particle_O, "stationary");
		token_root_sst_particle_stationary_O = json_tokens_getFromValue(tokens, string, token_root_sst_particle_stationary_V);
		token_root_sst_particle_stationary_alpha_V = json_tokens_getFromObject(tokens, string, token_root_sst_particle_stationary_O, "alpha");
		token_root_sst_particle_stationary_alpha_N = json_tokens_getFromValue(tokens, string, token_root_sst_particle_stationary_alpha_V);
		token_root_sst_particle_stationary_beta_V = json_tokens_getFromObject(tokens, string, token_root_sst_particle_stationary_O, "beta");
		token_root_sst_particle_stationary_beta_N = json_tokens_getFromValue(tokens, string, token_root_sst_particle_stationary_beta_V);
		token_root_sst_particle_stationary_ratio_V = json_tokens_getFromObject(tokens, string, token_root_sst_particle_stationary_O, "ratio");
		token_root_sst_particle_stationary_ratio_N = json_tokens_getFromValue(tokens, string, token_root_sst_particle_stationary_ratio_V);
		
		token_root_sst_particle_velocity_V = json_tokens_getFromObject(tokens, string, token_root_sst_particle_O, "velocity");
		token_root_sst_particle_velocity_O = json_tokens_getFromValue(tokens, string, token_root_sst_particle_velocity_V);
		token_root_sst_particle_velocity_alpha_V = json_tokens_getFromObject(tokens, string, token_root_sst_particle_velocity_O, "alpha");
		token_root_sst_particle_velocity_alpha_N = json_tokens_getFromValue(tokens, string, token_root_sst_particle_velocity_alpha_V);
		token_root_sst_particle_velocity_beta_V = json_tokens_getFromObject(tokens, string, token_root_sst_particle_velocity_O, "beta");
		token_root_sst_particle_velocity_beta_N = json_tokens_getFromValue(tokens, string, token_root_sst_particle_velocity_beta_V);
		token_root_sst_particle_velocity_ratio_V = json_tokens_getFromObject(tokens, string, token_root_sst_particle_velocity_O, "ratio");
		token_root_sst_particle_velocity_ratio_N = json_tokens_getFromValue(tokens, string, token_root_sst_particle_velocity_ratio_V);
		
		token_root_sst_particle_acceleration_V = json_tokens_getFromObject(tokens, string, token_root_sst_particle_O, "acceleration");
		token_root_sst_particle_acceleration_O = json_tokens_getFromValue(tokens, string, token_root_sst_particle_acceleration_V);
		token_root_sst_particle_acceleration_alpha_V = json_tokens_getFromObject(tokens, string, token_root_sst_particle_acceleration_O, "alpha");
		token_root_sst_particle_acceleration_alpha_N = json_tokens_getFromValue(tokens, string, token_root_sst_particle_acceleration_alpha_V);
		token_root_sst_particle_acceleration_beta_V = json_tokens_getFromObject(tokens, string, token_root_sst_particle_acceleration_O, "beta");
		token_root_sst_particle_acceleration_beta_N = json_tokens_getFromValue(tokens, string, token_root_sst_particle_acceleration_beta_V);
		token_root_sst_particle_acceleration_ratio_V = json_tokens_getFromObject(tokens, string, token_root_sst_particle_acceleration_O, "ratio");
		token_root_sst_particle_acceleration_ratio_N = json_tokens_getFromValue(tokens, string, token_root_sst_particle_acceleration_ratio_V);
		
		token_root_sst_particle_Nmin_V = json_tokens_getFromObject(tokens, string, token_root_sst_particle_O, "Nmin");
		token_root_sst_particle_Nmin_N = json_tokens_getFromValue(tokens, string, token_root_sst_particle_Nmin_V);

		token_root_sst_targets_V = json_tokens_getFromObject(tokens, string, token_root_sst_O, "targets");
		token_root_sst_targets_A = json_tokens_getFromValue(tokens, string, token_root_sst_targets_V);

		nTargets = json_tokens_count(tokens, string, token_root_sst_targets_A);

		for (iTarget = 0; iTarget < nTargets; iTarget++) {

			token_root_sst_targets_e_V[iTarget] = json_tokens_getFromArray(tokens, string, token_root_sst_targets_A, iTarget);
			token_root_sst_targets_e_O[iTarget] = json_tokens_getFromValue(tokens, string, token_root_sst_targets_e_V[iTarget]);

			token_root_sst_targets_e_tag_V[iTarget] = json_tokens_getFromObject(tokens, string, token_root_sst_targets_e_O[iTarget], "tag");
			token_root_sst_targets_e_tag_S[iTarget] = json_tokens_getFromValue(tokens, string, token_root_sst_targets_e_tag_V[iTarget]);
			token_root_sst_targets_e_x_V[iTarget] = json_tokens_getFromObject(tokens, string, token_root_sst_targets_e_O[iTarget], "x");
			token_root_sst_targets_e_x_N[iTarget] = json_tokens_getFromValue(tokens, string, token_root_sst_targets_e_x_V[iTarget]);
			token_root_sst_targets_e_y_V[iTarget] = json_tokens_getFromObject(tokens, string, token_root_sst_targets_e_O[iTarget], "y");
			token_root_sst_targets_e_y_N[iTarget] = json_tokens_getFromValue(tokens, string, token_root_sst_targets_e_y_V[iTarget]);
			token_root_sst_targets_e_z_V[iTarget] = json_tokens_getFromObject(tokens, string, token_root_sst_targets_e_O[iTarget], "z");
			token_root_sst_targets_e_z_N[iTarget] = json_tokens_getFromValue(tokens, string, token_root_sst_targets_e_z_V[iTarget]);

		}

		token_root_sst_input_V = json_tokens_getFromObject(tokens, string, token_root_sst_O, "input");
		token_root_sst_input_O = json_tokens_getFromValue(tokens, string, token_root_sst_input_V);
		token_root_sst_input_type_V = json_tokens_getFromObject(tokens, string, token_root_sst_input_O, "type");
		token_root_sst_input_type_S = json_tokens_getFromValue(tokens, string, token_root_sst_input_type_V);
		token_root_sst_input_file_V = json_tokens_getFromObject(tokens, string, token_root_sst_input_O, "file");
		token_root_sst_input_file_O = json_tokens_getFromValue(tokens, string, token_root_sst_input_file_V);
		token_root_sst_input_file_path_V = json_tokens_getFromObject(tokens, string, token_root_sst_input_file_O, "path");
		token_root_sst_input_file_path_S = json_tokens_getFromValue(tokens, string, token_root_sst_input_file_path_V);
		token_root_sst_input_socket_V = json_tokens_getFromObject(tokens, string, token_root_sst_input_O, "socket");
		token_root_sst_input_socket_O = json_tokens_getFromValue(tokens, string, token_root_sst_input_socket_V);
		token_root_sst_input_socket_port_V = json_tokens_getFromObject(tokens, string, token_root_sst_input_socket_O, "port");
		token_root_sst_input_socket_port_N = json_tokens_getFromValue(tokens, string, token_root_sst_input_socket_port_V);

		token_root_sst_output_V = json_tokens_getFromObject(tokens, string, token_root_sst_O, "output");
		token_root_sst_output_O = json_tokens_getFromValue(tokens, string, token_root_sst_output_V);
		token_root_sst_output_type_V = json_tokens_getFromObject(tokens, string, token_root_sst_output_O, "type");
		token_root_sst_output_type_S = json_tokens_getFromValue(tokens, string, token_root_sst_output_type_V);
		token_root_sst_output_file_V = json_tokens_getFromObject(tokens, string, token_root_sst_output_O, "file");
		token_root_sst_output_file_O = json_tokens_getFromValue(tokens, string, token_root_sst_output_file_V);
		token_root_sst_output_file_path_V = json_tokens_getFromObject(tokens, string, token_root_sst_output_file_O, "path");
		token_root_sst_output_file_path_S = json_tokens_getFromValue(tokens, string, token_root_sst_output_file_path_V);
		token_root_sst_output_socket_V = json_tokens_getFromObject(tokens, string, token_root_sst_output_O, "socket");
		token_root_sst_output_socket_O = json_tokens_getFromValue(tokens, string, token_root_sst_output_socket_V);
		token_root_sst_output_socket_port_V = json_tokens_getFromObject(tokens, string, token_root_sst_output_socket_O, "port");
		token_root_sst_output_socket_port_N = json_tokens_getFromValue(tokens, string, token_root_sst_output_socket_port_V);

		token_root_sss_V = json_tokens_getFromObject(tokens, string, token_root_O, "sss");
		token_root_sss_O = json_tokens_getFromValue(tokens, string, token_root_sss_V);

		token_root_sss_offset_V = json_tokens_getFromObject(tokens, string, token_root_sss_O, "offset");
		token_root_sss_offset_N = json_tokens_getFromValue(tokens, string, token_root_sss_offset_V);

		token_root_sss_separation_V = json_tokens_getFromObject(tokens, string, token_root_sss_O, "separation");
		token_root_sss_separation_O = json_tokens_getFromValue(tokens, string, token_root_sss_separation_V);

		token_root_sss_separation_mode_V = json_tokens_getFromObject(tokens, string, token_root_sss_separation_O, "mode");
		token_root_sss_separation_mode_S = json_tokens_getFromValue(tokens, string, token_root_sss_separation_mode_V);
		token_root_sss_separation_techniques_V = json_tokens_getFromObject(tokens, string, token_root_sss_separation_O, "techniques");
		token_root_sss_separation_techniques_O = json_tokens_getFromValue(tokens, string, token_root_sss_separation_techniques_V);
		token_root_sss_separation_techniques_dds_V = json_tokens_getFromObject(tokens, string, token_root_sss_separation_techniques_O, "dds");
		token_root_sss_separation_techniques_dds_O = json_tokens_getFromValue(tokens, string, token_root_sss_separation_techniques_dds_V);
		token_root_sss_separation_techniques_dgss_V = json_tokens_getFromObject(tokens, string, token_root_sss_separation_techniques_O, "dgss");
		token_root_sss_separation_techniques_dgss_O = json_tokens_getFromValue(tokens, string, token_root_sss_separation_techniques_dgss_V);
		token_root_sss_separation_techniques_dgss_mu_V = json_tokens_getFromObject(tokens, string, token_root_sss_separation_techniques_dgss_O, "mu");
		token_root_sss_separation_techniques_dgss_mu_N = json_tokens_getFromValue(tokens, string, token_root_sss_separation_techniques_dgss_mu_V);
		token_root_sss_separation_techniques_dgss_lambda_V = json_tokens_getFromObject(tokens, string, token_root_sss_separation_techniques_dgss_O, "lambda");
		token_root_sss_separation_techniques_dgss_lambda_N = json_tokens_getFromValue(tokens, string, token_root_sss_separation_techniques_dgss_lambda_V);
		token_root_sss_separation_techniques_dmvdr_V = json_tokens_getFromObject(tokens, string, token_root_sss_separation_techniques_O, "dmvdr");
		token_root_sss_separation_techniques_dmvdr_O = json_tokens_getFromValue(tokens, string, token_root_sss_separation_techniques_dmvdr_V);

		token_root_sss_separation_format_V = json_tokens_getFromObject(tokens, string, token_root_sss_separation_O, "format");
		token_root_sss_separation_format_O = json_tokens_getFromValue(tokens, string, token_root_sss_separation_format_V);
		token_root_sss_separation_format_fS_V = json_tokens_getFromObject(tokens, string, token_root_sss_separation_format_O, "fS");
		token_root_sss_separation_format_fS_N = json_tokens_getFromValue(tokens, string, token_root_sss_separation_format_fS_V);
		token_root_sss_separation_format_hopSize_V = json_tokens_getFromObject(tokens, string, token_root_sss_separation_format_O, "hopSize");
		token_root_sss_separation_format_hopSize_N = json_tokens_getFromValue(tokens, string, token_root_sss_separation_format_hopSize_V);
		token_root_sss_separation_format_nBits_V = json_tokens_getFromObject(tokens, string, token_root_sss_separation_format_O, "nBits");
		token_root_sss_separation_format_nBits_N = json_tokens_getFromValue(tokens, string, token_root_sss_separation_format_nBits_V);

		token_root_sss_separation_output_V = json_tokens_getFromObject(tokens, string, token_root_sss_separation_O, "output");
		token_root_sss_separation_output_O = json_tokens_getFromValue(tokens, string, token_root_sss_separation_output_V);
		token_root_sss_separation_output_type_V = json_tokens_getFromObject(tokens, string, token_root_sss_separation_output_O, "type");
		token_root_sss_separation_output_type_S = json_tokens_getFromValue(tokens, string, token_root_sss_separation_output_type_V);
		token_root_sss_separation_output_file_V = json_tokens_getFromObject(tokens, string, token_root_sss_separation_output_O, "file");
		token_root_sss_separation_output_file_O = json_tokens_getFromValue(tokens, string, token_root_sss_separation_output_file_V);
		token_root_sss_separation_output_file_path_V = json_tokens_getFromObject(tokens, string, token_root_sss_separation_output_file_O, "path");
		token_root_sss_separation_output_file_path_S = json_tokens_getFromValue(tokens, string, token_root_sss_separation_output_file_path_V);
		token_root_sss_separation_output_socket_V = json_tokens_getFromObject(tokens, string, token_root_sss_separation_output_O, "socket");
		token_root_sss_separation_output_socket_O = json_tokens_getFromValue(tokens, string, token_root_sss_separation_output_socket_V);
		token_root_sss_separation_output_socket_port_V = json_tokens_getFromObject(tokens, string, token_root_sss_separation_output_socket_O, "port");
		token_root_sss_separation_output_socket_port_N = json_tokens_getFromValue(tokens, string, token_root_sss_separation_output_socket_port_V);

		token_root_sss_postfiltering_V = json_tokens_getFromObject(tokens, string, token_root_sss_O, "postfiltering");
		token_root_sss_postfiltering_O = json_tokens_getFromValue(tokens, string, token_root_sss_postfiltering_V);

		token_root_sss_postfiltering_mode_V = json_tokens_getFromObject(tokens, string, token_root_sss_postfiltering_O, "mode");
		token_root_sss_postfiltering_mode_S = json_tokens_getFromValue(tokens, string, token_root_sss_postfiltering_mode_V);
		token_root_sss_postfiltering_techniques_V = json_tokens_getFromObject(tokens, string, token_root_sss_postfiltering_O, "techniques");
		token_root_sss_postfiltering_techniques_O = json_tokens_getFromValue(tokens, string, token_root_sss_postfiltering_techniques_V);
		token_root_sss_postfiltering_techniques_ms_V = json_tokens_getFromObject(tokens, string, token_root_sss_postfiltering_techniques_O, "ms");
		token_root_sss_postfiltering_techniques_ms_O = json_tokens_getFromValue(tokens, string, token_root_sss_postfiltering_techniques_ms_V);
		token_root_sss_postfiltering_techniques_ms_alphaPmin_V = json_tokens_getFromObject(tokens, string, token_root_sss_postfiltering_techniques_ms_O, "alphaPmin");
		token_root_sss_postfiltering_techniques_ms_alphaPmin_N = json_tokens_getFromValue(tokens, string, token_root_sss_postfiltering_techniques_ms_alphaPmin_V);
		token_root_sss_postfiltering_techniques_ms_eta_V = json_tokens_getFromObject(tokens, string, token_root_sss_postfiltering_techniques_ms_O, "eta");
		token_root_sss_postfiltering_techniques_ms_eta_N = json_tokens_getFromValue(tokens, string, token_root_sss_postfiltering_techniques_ms_eta_V);
		token_root_sss_postfiltering_techniques_ms_alphaZ_V = json_tokens_getFromObject(tokens, string, token_root_sss_postfiltering_techniques_ms_O, "alphaZ");
		token_root_sss_postfiltering_techniques_ms_alphaZ_N = json_tokens_getFromValue(tokens, string, token_root_sss_postfiltering_techniques_ms_alphaZ_V);
		token_root_sss_postfiltering_techniques_ms_thetaWin_V = json_tokens_getFromObject(tokens, string, token_root_sss_postfiltering_techniques_ms_O, "thetaWin");
		token_root_sss_postfiltering_techniques_ms_thetaWin_N = json_tokens_getFromValue(tokens, string, token_root_sss_postfiltering_techniques_ms_thetaWin_V);
		token_root_sss_postfiltering_techniques_ms_alphaWin_V = json_tokens_getFromObject(tokens, string, token_root_sss_postfiltering_techniques_ms_O, "alphaWin");
		token_root_sss_postfiltering_techniques_ms_alphaWin_N = json_tokens_getFromValue(tokens, string, token_root_sss_postfiltering_techniques_ms_alphaWin_V);
		token_root_sss_postfiltering_techniques_ms_maxAbsenceProb_V = json_tokens_getFromObject(tokens, string, token_root_sss_postfiltering_techniques_ms_O, "maxAbsenceProb");
		token_root_sss_postfiltering_techniques_ms_maxAbsenceProb_N = json_tokens_getFromValue(tokens, string, token_root_sss_postfiltering_techniques_ms_maxAbsenceProb_V);
		token_root_sss_postfiltering_techniques_ms_Gmin_V = json_tokens_getFromObject(tokens, string, token_root_sss_postfiltering_techniques_ms_O, "Gmin");
		token_root_sss_postfiltering_techniques_ms_Gmin_N = json_tokens_getFromValue(tokens, string, token_root_sss_postfiltering_techniques_ms_Gmin_V);
		token_root_sss_postfiltering_techniques_ms_winSizeLocal_V = json_tokens_getFromObject(tokens, string, token_root_sss_postfiltering_techniques_ms_O, "winSizeLocal");
		token_root_sss_postfiltering_techniques_ms_winSizeLocal_N = json_tokens_getFromValue(tokens, string, token_root_sss_postfiltering_techniques_ms_winSizeLocal_V);
		token_root_sss_postfiltering_techniques_ms_winSizeGlobal_V = json_tokens_getFromObject(tokens, string, token_root_sss_postfiltering_techniques_ms_O, "winSizeGlobal");
		token_root_sss_postfiltering_techniques_ms_winSizeGlobal_N = json_tokens_getFromValue(tokens, string, token_root_sss_postfiltering_techniques_ms_winSizeGlobal_V);
		token_root_sss_postfiltering_techniques_ms_winSizeFrame_V = json_tokens_getFromObject(tokens, string, token_root_sss_postfiltering_techniques_ms_O, "winSizeFrame");
		token_root_sss_postfiltering_techniques_ms_winSizeFrame_N = json_tokens_getFromValue(tokens, string, token_root_sss_postfiltering_techniques_ms_winSizeFrame_V);
		token_root_sss_postfiltering_techniques_ss_V = json_tokens_getFromObject(tokens, string, token_root_sss_postfiltering_techniques_O, "ss");
		token_root_sss_postfiltering_techniques_ss_O = json_tokens_getFromValue(tokens, string, token_root_sss_postfiltering_techniques_ss_V);
		token_root_sss_postfiltering_techniques_ss_Gmin_V = json_tokens_getFromObject(tokens, string, token_root_sss_postfiltering_techniques_ss_O, "Gmin");
		token_root_sss_postfiltering_techniques_ss_Gmin_N = json_tokens_getFromValue(tokens, string, token_root_sss_postfiltering_techniques_ss_Gmin_V);
		token_root_sss_postfiltering_techniques_ss_Gmid_V = json_tokens_getFromObject(tokens, string, token_root_sss_postfiltering_techniques_ss_O, "Gmid");
		token_root_sss_postfiltering_techniques_ss_Gmid_N = json_tokens_getFromValue(tokens, string, token_root_sss_postfiltering_techniques_ss_Gmid_V);
		token_root_sss_postfiltering_techniques_ss_Gslope_V = json_tokens_getFromObject(tokens, string, token_root_sss_postfiltering_techniques_ss_O, "Gslope");
		token_root_sss_postfiltering_techniques_ss_Gslope_N = json_tokens_getFromValue(tokens, string, token_root_sss_postfiltering_techniques_ss_Gslope_V);
		
		token_root_sss_postfiltering_format_V = json_tokens_getFromObject(tokens, string, token_root_sss_postfiltering_O, "format");
		token_root_sss_postfiltering_format_O = json_tokens_getFromValue(tokens, string, token_root_sss_postfiltering_format_V);
		token_root_sss_postfiltering_format_fS_V = json_tokens_getFromObject(tokens, string, token_root_sss_postfiltering_format_O, "fS");
		token_root_sss_postfiltering_format_fS_N = json_tokens_getFromValue(tokens, string, token_root_sss_postfiltering_format_fS_V);
		token_root_sss_postfiltering_format_hopSize_V = json_tokens_getFromObject(tokens, string, token_root_sss_postfiltering_format_O, "hopSize");
		token_root_sss_postfiltering_format_hopSize_N = json_tokens_getFromValue(tokens, string, token_root_sss_postfiltering_format_hopSize_V);
		token_root_sss_postfiltering_format_nBits_V = json_tokens_getFromObject(tokens, string, token_root_sss_postfiltering_format_O, "nBits");
		token_root_sss_postfiltering_format_nBits_N = json_tokens_getFromValue(tokens, string, token_root_sss_postfiltering_format_nBits_V);

		token_root_sss_postfiltering_output_V = json_tokens_getFromObject(tokens, string, token_root_sss_postfiltering_O, "output");
		token_root_sss_postfiltering_output_O = json_tokens_getFromValue(tokens, string, token_root_sss_postfiltering_output_V);
		token_root_sss_postfiltering_output_type_V = json_tokens_getFromObject(tokens, string, token_root_sss_postfiltering_output_O, "type");
		token_root_sss_postfiltering_output_type_S = json_tokens_getFromValue(tokens, string, token_root_sss_postfiltering_output_type_V);
		token_root_sss_postfiltering_output_file_V = json_tokens_getFromObject(tokens, string, token_root_sss_postfiltering_output_O, "file");
		token_root_sss_postfiltering_output_file_O = json_tokens_getFromValue(tokens, string, token_root_sss_postfiltering_output_file_V);
		token_root_sss_postfiltering_output_file_path_V = json_tokens_getFromObject(tokens, string, token_root_sss_postfiltering_output_file_O, "path");
		token_root_sss_postfiltering_output_file_path_S = json_tokens_getFromValue(tokens, string, token_root_sss_postfiltering_output_file_path_V);
		token_root_sss_postfiltering_output_socket_V = json_tokens_getFromObject(tokens, string, token_root_sss_postfiltering_output_O, "socket");
		token_root_sss_postfiltering_output_socket_O = json_tokens_getFromValue(tokens, string, token_root_sss_postfiltering_output_socket_V);
		token_root_sss_postfiltering_output_socket_port_V = json_tokens_getFromObject(tokens, string, token_root_sss_postfiltering_output_socket_O, "port");
		token_root_sss_postfiltering_output_socket_port_N = json_tokens_getFromValue(tokens, string, token_root_sss_postfiltering_output_socket_port_V);		

		// Access each token

		json_tokens_extractInt(tokens, string, token_root_raw_format_fS_N, &(sets->raw.format.fS));
		json_tokens_extractInt(tokens, string, token_root_raw_format_hopSize_N, &(sets->raw.format.hopSize));
		json_tokens_extractInt(tokens, string, token_root_raw_format_nBits_N, &(sets->raw.format.nBits));
		json_tokens_extractInt(tokens, string, token_root_raw_nChannels_N, &(sets->raw.nChannels));

		json_tokens_extractString(tokens, string, token_root_raw_input_type_S, sets->raw.input.type);
		json_tokens_extractString(tokens, string, token_root_raw_input_file_path_S, sets->raw.input.file.path);
		json_tokens_extractInt(tokens, string, token_root_raw_input_socket_port_N, &(sets->raw.input.socket.port));
		json_tokens_extractString(tokens, string, token_root_raw_input_soundcard_device_S, sets->raw.input.soundcard.device);

		json_tokens_extractString(tokens, string, token_root_raw_output_type_S, sets->raw.output.type);
		json_tokens_extractString(tokens, string, token_root_raw_output_file_path_S, sets->raw.output.file.path);
		json_tokens_extractInt(tokens, string, token_root_raw_output_socket_port_N, &(sets->raw.output.socket.port));

		sets->mapping.N = nChannels;

		for (iChannel = 0; iChannel < nChannels; iChannel++) {

			json_tokens_extractInt(tokens, string, token_root_mapping_map_e_N[iChannel], &(sets->mapping.array[iChannel]));

		}

		json_tokens_extractFloat(tokens, string, token_root_general_epsilon_N, &(sets->general.epsilon));
		json_tokens_extractInt(tokens, string, token_root_general_size_hopSize_N, &(sets->general.size.hopSize));
		json_tokens_extractInt(tokens, string, token_root_general_size_frameSize_N, &(sets->general.size.frameSize));
		json_tokens_extractInt(tokens, string, token_root_general_samplerate_mu_N, &(sets->general.samplerate.mu));
		json_tokens_extractFloat(tokens, string, token_root_general_samplerate_sigma2_N, &(sets->general.samplerate.sigma2));
		json_tokens_extractFloat(tokens, string, token_root_general_speedofsound_mu_N, &(sets->general.speedofsound.mu));
		json_tokens_extractFloat(tokens, string, token_root_general_speedofsound_sigma2_N, &(sets->general.speedofsound.sigma2));

		sets->general.mics.N = nMics;

		for (iMic = 0; iMic < nMics; iMic++) {

			json_tokens_extractFloat(tokens, string, token_root_general_mics_e_mus_0_N[iMic], &(sets->general.mics.array[iMic].mu[0]));
			json_tokens_extractFloat(tokens, string, token_root_general_mics_e_mus_1_N[iMic], &(sets->general.mics.array[iMic].mu[1]));
			json_tokens_extractFloat(tokens, string, token_root_general_mics_e_mus_2_N[iMic], &(sets->general.mics.array[iMic].mu[2]));

			json_tokens_extractFloat(tokens, string, token_root_general_mics_e_sigma2s_0_N[iMic], &(sets->general.mics.array[iMic].sigma2[0]));
			json_tokens_extractFloat(tokens, string, token_root_general_mics_e_sigma2s_1_N[iMic], &(sets->general.mics.array[iMic].sigma2[1]));
			json_tokens_extractFloat(tokens, string, token_root_general_mics_e_sigma2s_2_N[iMic], &(sets->general.mics.array[iMic].sigma2[2]));
			json_tokens_extractFloat(tokens, string, token_root_general_mics_e_sigma2s_3_N[iMic], &(sets->general.mics.array[iMic].sigma2[3]));
			json_tokens_extractFloat(tokens, string, token_root_general_mics_e_sigma2s_4_N[iMic], &(sets->general.mics.array[iMic].sigma2[4]));
			json_tokens_extractFloat(tokens, string, token_root_general_mics_e_sigma2s_5_N[iMic], &(sets->general.mics.array[iMic].sigma2[5]));
			json_tokens_extractFloat(tokens, string, token_root_general_mics_e_sigma2s_6_N[iMic], &(sets->general.mics.array[iMic].sigma2[6]));
			json_tokens_extractFloat(tokens, string, token_root_general_mics_e_sigma2s_7_N[iMic], &(sets->general.mics.array[iMic].sigma2[7]));
			json_tokens_extractFloat(tokens, string, token_root_general_mics_e_sigma2s_8_N[iMic], &(sets->general.mics.array[iMic].sigma2[8]));

			json_tokens_extractFloat(tokens, string, token_root_general_mics_e_directions_0_N[iMic], &(sets->general.mics.array[iMic].direction[0]));
			json_tokens_extractFloat(tokens, string, token_root_general_mics_e_directions_1_N[iMic], &(sets->general.mics.array[iMic].direction[1]));
			json_tokens_extractFloat(tokens, string, token_root_general_mics_e_directions_2_N[iMic], &(sets->general.mics.array[iMic].direction[2]));

			json_tokens_extractFloat(tokens, string, token_root_general_mics_e_angles_0_N[iMic], &(sets->general.mics.array[iMic].angle[0]));
			json_tokens_extractFloat(tokens, string, token_root_general_mics_e_angles_1_N[iMic], &(sets->general.mics.array[iMic].angle[1]));

		}

		sets->general.spatialfilters.N = nSpatialFilters;

		for (iSpatialFilter = 0; iSpatialFilter < nSpatialFilters; iSpatialFilter++) {

			json_tokens_extractFloat(tokens, string, token_root_general_spatialfilters_e_directions_0_N[iSpatialFilter], &(sets->general.spatialfilters.array[iSpatialFilter].direction[0]));
			json_tokens_extractFloat(tokens, string, token_root_general_spatialfilters_e_directions_1_N[iSpatialFilter], &(sets->general.spatialfilters.array[iSpatialFilter].direction[1]));
			json_tokens_extractFloat(tokens, string, token_root_general_spatialfilters_e_directions_2_N[iSpatialFilter], &(sets->general.spatialfilters.array[iSpatialFilter].direction[2]));

			json_tokens_extractFloat(tokens, string, token_root_general_spatialfilters_e_angles_0_N[iSpatialFilter], &(sets->general.spatialfilters.array[iSpatialFilter].angle[0]));
			json_tokens_extractFloat(tokens, string, token_root_general_spatialfilters_e_angles_1_N[iSpatialFilter], &(sets->general.spatialfilters.array[iSpatialFilter].angle[1]));

		}

		json_tokens_extractInt(tokens, string, token_root_general_nthetas_N, &(sets->general.nThetas));
		json_tokens_extractFloat(tokens, string, token_root_general_gainmin_N, &(sets->general.gainMin));

		json_tokens_extractInt(tokens, string, token_root_sne_b_N, &(sets->sne.b));
		json_tokens_extractFloat(tokens, string, token_root_sne_alphaS_N, &(sets->sne.alphaS));
		json_tokens_extractInt(tokens, string, token_root_sne_L_N, &(sets->sne.L));
		json_tokens_extractFloat(tokens, string, token_root_sne_delta_N, &(sets->sne.delta));
		json_tokens_extractFloat(tokens, string, token_root_sne_alphaD_N, &(sets->sne.alphaD));

		json_tokens_extractInt(tokens, string, token_root_ssl_nPots_N, &(sets->ssl.nPots));
		json_tokens_extractInt(tokens, string, token_root_ssl_nMatches_N, &(sets->ssl.nMatches));
		json_tokens_extractFloat(tokens, string, token_root_ssl_probMin_N, &(sets->ssl.probMin));
		json_tokens_extractInt(tokens, string, token_root_ssl_nRefinedLevels_N, &(sets->ssl.nRefinedLevels));
		json_tokens_extractInt(tokens, string, token_root_ssl_interpRate_N, &(sets->ssl.interpRate));

		sets->ssl.scans.N = nScans;

		for (iScan = 0; iScan < nScans; iScan++) {

			json_tokens_extractInt(tokens, string, token_root_ssl_scans_e_level_N[iScan], &(sets->ssl.scans.array[iScan].level));
			json_tokens_extractInt(tokens, string, token_root_ssl_scans_e_delta_N[iScan], &(sets->ssl.scans.array[iScan].delta));

		}

		json_tokens_extractString(tokens, string, token_root_ssl_output_type_S, sets->ssl.output.type);
		json_tokens_extractString(tokens, string, token_root_ssl_output_file_path_S, sets->ssl.output.file.path);
		json_tokens_extractInt(tokens, string, token_root_ssl_output_socket_port_N, &(sets->ssl.output.socket.port));

		json_tokens_extractString(tokens, string, token_root_sst_mode_S, sets->sst.mode);
		json_tokens_extractString(tokens, string, token_root_sst_add_S, sets->sst.add);

		sets->sst.active.N = nGaussiansActive;

		for (iGaussianActive = 0; iGaussianActive < nGaussiansActive; iGaussianActive++) {

			json_tokens_extractFloat(tokens, string, token_root_sst_energy_active_e_weight_N[iGaussianActive], &(sets->sst.active.array[iGaussianActive].weight));
			json_tokens_extractFloat(tokens, string, token_root_sst_energy_active_e_mu_N[iGaussianActive], &(sets->sst.active.array[iGaussianActive].mu));
			json_tokens_extractFloat(tokens, string, token_root_sst_energy_active_e_sigma2_N[iGaussianActive], &(sets->sst.active.array[iGaussianActive].sigma2));

		}

		sets->sst.inactive.N = nGaussiansInactive;

		for (iGaussianInactive = 0; iGaussianInactive < nGaussiansInactive; iGaussianInactive++) {

			json_tokens_extractFloat(tokens, string, token_root_sst_energy_inactive_e_weight_N[iGaussianInactive], &(sets->sst.inactive.array[iGaussianInactive].weight));
			json_tokens_extractFloat(tokens, string, token_root_sst_energy_inactive_e_mu_N[iGaussianInactive], &(sets->sst.inactive.array[iGaussianInactive].mu));
			json_tokens_extractFloat(tokens, string, token_root_sst_energy_inactive_e_sigma2_N[iGaussianInactive], &(sets->sst.inactive.array[iGaussianInactive].sigma2));

		}		

		json_tokens_extractFloat(tokens, string, token_root_sst_sigmaR2_prob_N, &(sets->sst.sigmaR2.prob));
		json_tokens_extractFloat(tokens, string, token_root_sst_sigmaR2_active_N, &(sets->sst.sigmaR2.active));
		json_tokens_extractFloat(tokens, string, token_root_sst_sigmaR2_target_N, &(sets->sst.sigmaR2.target));

		json_tokens_extractFloat(tokens, string, token_root_sst_P_false_N, &(sets->sst.P.pFalse));
		json_tokens_extractFloat(tokens, string, token_root_sst_P_new_N, &(sets->sst.P.pNew));
		json_tokens_extractFloat(tokens, string, token_root_sst_P_track_N, &(sets->sst.P.pTrack));

		json_tokens_extractFloat(tokens, string, token_root_sst_levels_new_theta_N, &(sets->sst.levels.lNew.theta));
		sets->sst.levels.lNew.N = 0;
		
		json_tokens_extractFloat(tokens, string, token_root_sst_levels_prob_theta_N, &(sets->sst.levels.lProb.theta));
		sets->sst.levels.lProb.N = 1;
		json_tokens_extractInt(tokens, string, token_root_sst_levels_prob_N_N, &(sets->sst.levels.lProb.Ns[0]));
		
		json_tokens_extractFloat(tokens, string, token_root_sst_levels_inactive_theta_N, &(sets->sst.levels.lInactive.theta));
		sets->sst.levels.lInactive.N = nLevels;		
		for (iLevel = 0; iLevel < nLevels; iLevel++) {
			json_tokens_extractInt(tokens, string, token_root_sst_levels_inactive_Ns_e_N[iLevel], &(sets->sst.levels.lInactive.Ns[iLevel]));
		}

		json_tokens_extractFloat(tokens, string, token_root_sst_kalman_sigmaQ_N, &(sets->sst.kalman.sigmaQ));

		json_tokens_extractInt(tokens, string, token_root_sst_particle_nParticles_N, &(sets->sst.particle.nParticles));
		json_tokens_extractFloat(tokens, string, token_root_sst_particle_stationary_alpha_N, &(sets->sst.particle.stationary.alpha));
		json_tokens_extractFloat(tokens, string, token_root_sst_particle_stationary_beta_N, &(sets->sst.particle.stationary.beta));
		json_tokens_extractFloat(tokens, string, token_root_sst_particle_stationary_ratio_N, &(sets->sst.particle.stationary.ratio));
		json_tokens_extractFloat(tokens, string, token_root_sst_particle_velocity_alpha_N, &(sets->sst.particle.velocity.alpha));
		json_tokens_extractFloat(tokens, string, token_root_sst_particle_velocity_beta_N, &(sets->sst.particle.velocity.beta));
		json_tokens_extractFloat(tokens, string, token_root_sst_particle_velocity_ratio_N, &(sets->sst.particle.velocity.ratio));
		json_tokens_extractFloat(tokens, string, token_root_sst_particle_acceleration_alpha_N, &(sets->sst.particle.acceleration.alpha));
		json_tokens_extractFloat(tokens, string, token_root_sst_particle_acceleration_beta_N, &(sets->sst.particle.acceleration.beta));
		json_tokens_extractFloat(tokens, string, token_root_sst_particle_acceleration_ratio_N, &(sets->sst.particle.acceleration.ratio));
		json_tokens_extractFloat(tokens, string, token_root_sst_particle_Nmin_N, &(sets->sst.particle.Nmin));

		sets->sst.targets.N = nTargets;

		for (iTarget = 0; iTarget < nTargets; iTarget++) {

			json_tokens_extractString(tokens, string, token_root_sst_targets_e_tag_S[iTarget], sets->sst.targets.array[iTarget].tag);
			json_tokens_extractFloat(tokens, string, token_root_sst_targets_e_x_N[iTarget], &(sets->sst.targets.array[iTarget].x));
			json_tokens_extractFloat(tokens, string, token_root_sst_targets_e_y_N[iTarget], &(sets->sst.targets.array[iTarget].y));
			json_tokens_extractFloat(tokens, string, token_root_sst_targets_e_z_N[iTarget], &(sets->sst.targets.array[iTarget].z));

		}

		json_tokens_extractString(tokens, string, token_root_sst_input_type_S, sets->sst.input.type);
		json_tokens_extractString(tokens, string, token_root_sst_input_file_path_S, sets->sst.input.file.path);
		json_tokens_extractInt(tokens, string, token_root_sst_input_socket_port_N, &(sets->sst.input.socket.port));

		json_tokens_extractString(tokens, string, token_root_sst_output_type_S, sets->sst.output.type);
		json_tokens_extractString(tokens, string, token_root_sst_output_file_path_S, sets->sst.output.file.path);
		json_tokens_extractInt(tokens, string, token_root_sst_output_socket_port_N, &(sets->sst.output.socket.port));

		json_tokens_extractInt(tokens, string, token_root_sss_offset_N, &(sets->sss.offset));

		json_tokens_extractString(tokens, string, token_root_sss_separation_mode_S, sets->sss.separation.mode);
		json_tokens_extractFloat(tokens, string, token_root_sss_separation_techniques_dgss_mu_N, &(sets->sss.separation.techniques.dgss.mu));
		json_tokens_extractFloat(tokens, string, token_root_sss_separation_techniques_dgss_lambda_N, &(sets->sss.separation.techniques.dgss.lambda));

		json_tokens_extractInt(tokens, string, token_root_sss_separation_format_fS_N, &(sets->sss.separation.format.fS));		
		json_tokens_extractInt(tokens, string, token_root_sss_separation_format_hopSize_N, &(sets->sss.separation.format.hopSize));
		json_tokens_extractInt(tokens, string, token_root_sss_separation_format_nBits_N, &(sets->sss.separation.format.nBits));

		json_tokens_extractString(tokens, string, token_root_sss_separation_output_type_S, sets->sss.separation.output.type);
		json_tokens_extractString(tokens, string, token_root_sss_separation_output_file_path_S, sets->sss.separation.output.file.path);
		json_tokens_extractInt(tokens, string, token_root_sss_separation_output_socket_port_N, &(sets->sss.separation.output.socket.port));

		json_tokens_extractString(tokens, string, token_root_sss_postfiltering_mode_S, sets->sss.postfiltering.mode);
		json_tokens_extractFloat(tokens, string, token_root_sss_postfiltering_techniques_ms_alphaPmin_N, &(sets->sss.postfiltering.techniques.ms.alphaPmin));
		json_tokens_extractFloat(tokens, string, token_root_sss_postfiltering_techniques_ms_eta_N, &(sets->sss.postfiltering.techniques.ms.eta));
		json_tokens_extractFloat(tokens, string, token_root_sss_postfiltering_techniques_ms_alphaZ_N, &(sets->sss.postfiltering.techniques.ms.alphaZ));
		json_tokens_extractFloat(tokens, string, token_root_sss_postfiltering_techniques_ms_thetaWin_N, &(sets->sss.postfiltering.techniques.ms.thetaWin));
		json_tokens_extractFloat(tokens, string, token_root_sss_postfiltering_techniques_ms_alphaWin_N, &(sets->sss.postfiltering.techniques.ms.alphaWin));
		json_tokens_extractFloat(tokens, string, token_root_sss_postfiltering_techniques_ms_maxAbsenceProb_N, &(sets->sss.postfiltering.techniques.ms.maxAbsenceProb));
		json_tokens_extractFloat(tokens, string, token_root_sss_postfiltering_techniques_ms_Gmin_N, &(sets->sss.postfiltering.techniques.ms.Gmin));
		json_tokens_extractInt(tokens, string, token_root_sss_postfiltering_techniques_ms_winSizeLocal_N, &(sets->sss.postfiltering.techniques.ms.winSizeLocal));
		json_tokens_extractInt(tokens, string, token_root_sss_postfiltering_techniques_ms_winSizeGlobal_N, &(sets->sss.postfiltering.techniques.ms.winSizeGlobal));
		json_tokens_extractInt(tokens, string, token_root_sss_postfiltering_techniques_ms_winSizeFrame_N, &(sets->sss.postfiltering.techniques.ms.winSizeFrame));
		json_tokens_extractFloat(tokens, string, token_root_sss_postfiltering_techniques_ss_Gmin_N, &(sets->sss.postfiltering.techniques.ss.Gmin));
		json_tokens_extractFloat(tokens, string, token_root_sss_postfiltering_techniques_ss_Gmid_N, &(sets->sss.postfiltering.techniques.ss.Gmid));
		json_tokens_extractFloat(tokens, string, token_root_sss_postfiltering_techniques_ss_Gslope_N, &(sets->sss.postfiltering.techniques.ss.Gslope));

		json_tokens_extractInt(tokens, string, token_root_sss_postfiltering_format_fS_N, &(sets->sss.postfiltering.format.fS));		
		json_tokens_extractInt(tokens, string, token_root_sss_postfiltering_format_hopSize_N, &(sets->sss.postfiltering.format.hopSize));
		json_tokens_extractInt(tokens, string, token_root_sss_postfiltering_format_nBits_N, &(sets->sss.postfiltering.format.nBits));

		json_tokens_extractString(tokens, string, token_root_sss_postfiltering_output_type_S, sets->sss.postfiltering.output.type);
		json_tokens_extractString(tokens, string, token_root_sss_postfiltering_output_file_path_S, sets->sss.postfiltering.output.file.path);
		json_tokens_extractInt(tokens, string, token_root_sss_postfiltering_output_socket_port_N, &(sets->sss.postfiltering.output.socket.port));

		// Free

		free((void *) line);
		free((void *) string);
		json_tokens_destroy(tokens);

	}

	void settings_printf(const settings * sets) {

		unsigned int n;
		unsigned int d;

		printf("raw.format.fS = %u\n", sets->raw.format.fS);
		printf("raw.format.hopSize = %u\n", sets->raw.format.hopSize);
		printf("raw.format.nBits = %u\n", sets->raw.format.nBits);
		printf("raw.nChannels = %u\n", sets->raw.nChannels);
		printf("raw.input.type = \"%s\"\n", sets->raw.input.type);
		printf("raw.input.file.path = \"%s\"\n", sets->raw.input.file.path);
		printf("raw.input.socket.port = %u\n", sets->raw.input.socket.port);
		printf("raw.input.soundcard.device = \"%s\"\n", sets->raw.input.soundcard.device);
		printf("raw.output.type = \"%s\"\n", sets->raw.output.type);
		printf("raw.output.file.path = \"%s\"\n", sets->raw.output.file.path);
		printf("raw.output.socket.port = %u\n", sets->raw.output.socket.port);

		printf("\n");

		printf("mapping.map = [ ");

		for (n = 0; n < sets->mapping.N; n++) {

			printf("%u ", sets->mapping.array[n]);

		}

		printf("]\n");

		printf("\n");

		printf("general.epsilon = %e\n", sets->general.epsilon);
		printf("general.size.hopSize = %u\n", sets->general.size.hopSize);
		printf("general.size.frameSize = %u\n", sets->general.size.frameSize);
		printf("general.samplerate.mu = %u\n", sets->general.samplerate.mu);
		printf("general.samplerate.sigma2 = %f\n", sets->general.samplerate.sigma2);
		printf("general.speedofsound.mu = %f\n", sets->general.speedofsound.mu);
		printf("general.speedofsound.sigma2 = %f\n", sets->general.speedofsound.sigma2);

		for (n = 0; n < sets->general.mics.N; n++) {

			printf("general.mics[%u].mu = [ ", n);
			for (d = 0; d < 3; d++) {
				printf("%f ", sets->general.mics.array[n].mu[d]);
			}
			printf("]\n");

			printf("general.mics[%u].sigma2 = [ ", n);
			for (d = 0; d < 9; d++) {
				printf("%f ", sets->general.mics.array[n].sigma2[d]);
			}
			printf("]\n");

			printf("general.mics[%u].direction = [ ", n);
			for (d = 0; d < 3; d++) {
				printf("%f ", sets->general.mics.array[n].direction[d]);
			}
			printf("]\n");

			printf("general.mics[%u].angle = [ ", n);
			for (d = 0; d < 2; d++) {
				printf("%f ", sets->general.mics.array[n].angle[d]);
			}
			printf("]\n");

		}

		for (n = 0; n < sets->general.spatialfilters.N; n++) {

			printf("general.spatialfilters[%u].direction = [ ", n);
			for (d = 0; d < 3; d++) {
				printf("%f ", sets->general.spatialfilters.array[n].direction[d]);
			}
			printf("]\n");

			printf("general.spatialfilters[%u].angle = [ ", n);
			for (d = 0; d < 2; d++) {
				printf("%f ", sets->general.spatialfilters.array[n].angle[d]);
			}
			printf("]\n");			

		}

		printf("general.nThetas = %u\n", sets->general.nThetas);
		printf("general.gainMin = %f\n", sets->general.gainMin);

		printf("\n");

		printf("sne.b = %u\n", sets->sne.b);
		printf("sne.alphaS = %f\n", sets->sne.alphaS);
		printf("sne.L = %u\n", sets->sne.L);
		printf("sne.delta = %f\n", sets->sne.delta);
		printf("sne.alphaD = %f\n", sets->sne.alphaD);

		printf("\n");

		printf("ssl.nPots = %u\n", sets->ssl.nPots);
		printf("ssl.nMatches = %u\n", sets->ssl.nMatches);
		printf("ssl.probMin = %f\n", sets->ssl.probMin);
		printf("ssl.nRefinedLevels = %u\n", sets->ssl.nRefinedLevels);
		printf("ssl.interpRate = %u\n", sets->ssl.interpRate);

		for (n = 0; n < sets->ssl.scans.N; n++) {

			printf("ssl.scans[%u].level = %u\n", n, sets->ssl.scans.array[n].level);
			printf("ssl.scans[%u].delta = %d\n", n, sets->ssl.scans.array[n].delta);

		}

		printf("ssl.output.type = \"%s\"\n", sets->ssl.output.type);
		printf("ssl.output.file.path = \"%s\"\n", sets->ssl.output.file.path);
		printf("ssl.output.socket.port = %u\n", sets->ssl.output.socket.port);

		printf("\n");

		printf("sst.mode = %s­\n", sets->sst.mode);
		printf("sst.add = %s\n", sets->sst.add);

		for (n = 0; n < sets->sst.inactive.N; n++) {

			printf("sst.energy.inactive[%u].weight = %f\n", n, sets->sst.inactive.array[n].weight);
			printf("sst.energy.inactive[%u].mu = %f\n", n, sets->sst.inactive.array[n].mu);
			printf("sst.energy.inactive[%u].sigma2 = %f\n", n, sets->sst.inactive.array[n].sigma2);

		}

		for (n = 0; n < sets->sst.active.N; n++) {

			printf("sst.energy.active[%u].weight = %f\n", n, sets->sst.active.array[n].weight);
			printf("sst.energy.active[%u].mu = %f\n", n, sets->sst.active.array[n].mu);
			printf("sst.energy.active[%u].sigma2 = %f\n", n, sets->sst.active.array[n].sigma2);

		}

		printf("sst.sigmaR2.prob = %f\n", sets->sst.sigmaR2.prob);
		printf("sst.sigmaR2.active = %f\n", sets->sst.sigmaR2.active);
		printf("sst.sigmaR2.target = %f\n", sets->sst.sigmaR2.target);

		printf("sst.P.false = %f\n", sets->sst.P.pFalse);
		printf("sst.P.new = %f\n", sets->sst.P.pNew);
		printf("sst.P.track = %f\n", sets->sst.P.pTrack);

		printf("sst.levels.lNew.theta = %f\n", sets->sst.levels.lNew.theta);
		printf("sst.levels.lProb.theta = %f\n", sets->sst.levels.lProb.theta);
		printf("sst.levels.lProb.N = %u\n", sets->sst.levels.lProb.Ns[0]);
		printf("sst.levels.lInactive.theta = %f\n", sets->sst.levels.lInactive.theta);

		for (n = 0; n < sets->sst.levels.lInactive.N; n++) {
			printf("sst.levels.lInactive.Ns[%u] = %u\n", n, sets->sst.levels.lInactive.Ns[n]);
		}

		printf("sst.kalman.sigmaQ = %f\n", sets->sst.kalman.sigmaQ);

		printf("sst.particle.nParticles = %u\n", sets->sst.particle.nParticles);
		printf("sst.particle.stationary.alpha = %f\n", sets->sst.particle.stationary.alpha);
		printf("sst.particle.stationary.beta = %f\n", sets->sst.particle.stationary.beta);
		printf("sst.particle.stationary.ratio = %f\n", sets->sst.particle.stationary.ratio);
		printf("sst.particle.velocity.alpha = %f\n", sets->sst.particle.velocity.alpha);
		printf("sst.particle.velocity.beta = %f\n", sets->sst.particle.velocity.beta);
		printf("sst.particle.velocity.ratio = %f\n", sets->sst.particle.velocity.ratio);
		printf("sst.particle.acceleration.alpha = %f\n", sets->sst.particle.acceleration.alpha);
		printf("sst.particle.acceleration.beta = %f\n", sets->sst.particle.acceleration.beta);
		printf("sst.particle.acceleration.ratio = %f\n", sets->sst.particle.acceleration.ratio);
		printf("sst.particle.Nmin = %f\n", sets->sst.particle.Nmin);

		for (n = 0; n < sets->sst.targets.N; n++) {
			printf("sst.targets[%u].tag = \"%s\"\n", n, sets->sst.targets.array[n].tag);
			printf("sst.targets[%u].x = %f\n", n, sets->sst.targets.array[n].x);
			printf("sst.targets[%u].y = %f\n", n, sets->sst.targets.array[n].y);
			printf("sst.targets[%u].z = %f\n", n, sets->sst.targets.array[n].z);
		}

		printf("sst.input.type = \"%s\"\n", sets->sst.input.type);
		printf("sst.input.file.path = \"%s\"\n", sets->sst.input.file.path);
		printf("sst.input.socket.port = %u\n", sets->sst.input.socket.port);
		printf("sst.output.type = \"%s\"\n", sets->sst.output.type);
		printf("sst.output.file.path = \"%s\"\n", sets->sst.output.file.path);
		printf("sst.output.socket.port = %u\n", sets->sst.output.socket.port);

		printf("\n");

		printf("sss.offset = %u\n", sets->sss.offset);
		printf("sss.separation.mode = \"%s\"\n", sets->sss.separation.mode);
		printf("sss.separation.techniques.dgss.mu = %f\n", sets->sss.separation.techniques.dgss.mu);
		printf("sss.separation.techniques.dgss.lambda = %f\n", sets->sss.separation.techniques.dgss.lambda);
		printf("sss.separation.format.fS = %u\n", sets->sss.separation.format.fS);
		printf("sss.separation.format.hopSize = %u\n", sets->sss.separation.format.hopSize);
		printf("sss.separation.format.nBits = %u\n", sets->sss.separation.format.nBits);
		printf("sss.separation.output.type = \"%s\"\n", sets->sss.separation.output.type);
		printf("sss.separation.output.file.path = \"%s\"\n", sets->sss.separation.output.file.path);
		printf("sss.separation.output.socket.port = %u\n", sets->sss.separation.output.socket.port);
		printf("sss.postfiltering.mode = \"%s\"\n", sets->sss.postfiltering.mode);
		printf("sss.postfiltering.techniques.ms.alphaPmin = %f\n", sets->sss.postfiltering.techniques.ms.alphaPmin);
		printf("sss.postfiltering.techniques.ms.eta = %f\n", sets->sss.postfiltering.techniques.ms.eta);
		printf("sss.postfiltering.techniques.ms.alphaZ = %f\n", sets->sss.postfiltering.techniques.ms.alphaZ);
		printf("sss.postfiltering.techniques.ms.thetaWin = %f\n", sets->sss.postfiltering.techniques.ms.thetaWin);
		printf("sss.postfiltering.techniques.ms.alphaWin = %f\n", sets->sss.postfiltering.techniques.ms.alphaWin);
		printf("sss.postfiltering.techniques.ms.maxAbsenceProb = %f\n", sets->sss.postfiltering.techniques.ms.maxAbsenceProb);
		printf("sss.postfiltering.techniques.ms.Gmin = %f\n", sets->sss.postfiltering.techniques.ms.Gmin);
		printf("sss.postfiltering.techniques.ms.winSizeLocal = %u\n", sets->sss.postfiltering.techniques.ms.winSizeLocal);
		printf("sss.postfiltering.techniques.ms.winSizeGlobal = %u\n", sets->sss.postfiltering.techniques.ms.winSizeGlobal);
		printf("sss.postfiltering.techniques.ms.winSizeFrame = %u\n", sets->sss.postfiltering.techniques.ms.winSizeFrame);
		printf("sss.postfiltering.techniques.ss.Gmin = %f\n", sets->sss.postfiltering.techniques.ss.Gmin);
		printf("sss.postfiltering.techniques.ss.Gmid = %f\n", sets->sss.postfiltering.techniques.ss.Gmid);
		printf("sss.postfiltering.techniques.ss.Gslope = %f\n", sets->sss.postfiltering.techniques.ss.Gslope);
		printf("sss.postfiltering.format.fS = %u\n", sets->sss.postfiltering.format.fS);
		printf("sss.postfiltering.format.hopSize = %u\n", sets->sss.postfiltering.format.hopSize);
		printf("sss.postfiltering.format.nBits = %u\n", sets->sss.postfiltering.format.nBits);
		printf("sss.postfiltering.output.type = \"%s\"\n", sets->sss.postfiltering.output.type);
		printf("sss.postfiltering.output.file.path = \"%s\"\n", sets->sss.postfiltering.output.file.path);
		printf("sss.postfiltering.output.socket.port = %u\n", sets->sss.postfiltering.output.socket.port);

	}
