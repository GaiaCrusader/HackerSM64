// yoshi_rideable.inc.c

struct MarioState *player;
struct MarioState *rider;
f32 oYoshiIdleTimer;
f32 distanceToPlayer;

void bhv_yoshi_rideable_init(void) {
    o->oGravity = -3.0f;
    o->oFriction = 1.0f;
    
    o->activeFlags |= ACTIVE_FLAG_DESTRUCTIVE_OBJ_DONT_DESTROY;
    
    cur_obj_init_animation(YOSHI_ANIM_IDLE);
}

void bhv_yoshi_rideable_loop(void) {
    player = nearest_mario_state_to_object(o);
    distanceToPlayer = dist_between_objects(o, player->marioObj);
    
    if (o->oAction == YOSHI_ACT_IDLE) {
        oYoshiIdleTimer += 1;
        cur_obj_move_standard(-78);
        cur_obj_update_floor_and_walls();
        cur_obj_if_hit_wall_bounce_away();
        if (distanceToPlayer < 100) push_mario_out_of_object(player, o, 2);
        
        if (oYoshiIdleTimer >= 600) {
            spawn_mist_particles_with_sound(SOUND_OBJ_DYING_ENEMY1);
            obj_mark_for_deletion(o);
	}
    
        s32 yoshiRidingActions[] = {
	    ACT_RIDE_YOSHI_IDLE,
	    ACT_RIDE_YOSHI_WALK,
	    ACT_RIDE_YOSHI_JUMP,
	    ACT_RIDE_YOSHI_FALL,
	    ACT_RIDE_YOSHI_FLUTTER
        };

        if (!yoshiRidingActions[player->action]) {
            if ((player->vel[1] < 0) && distanceToPlayer < 80) {
                cur_obj_play_sound_2(SOUND_GENERAL_YOSHI_TALK);
                player->interactObj = o;
                player->usedObj = o;
                player->riddenObj = o;
		o->oAction = 1;
		o->heldByPlayerIndex = player->playerID;
		set_mario_action(player, ACT_RIDE_YOSHI_IDLE, 0);
	    }
	}
    } else if (o->oAction == 1) {
	s32 animFrame = o->header.gfx.animInfo.animFrame;
	rider = &gMarioStates[o->heldByPlayerIndex];
        oYoshiIdleTimer = 0;
        
        obj_copy_pos(o, rider->marioObj);
        o->oMoveAngleYaw = rider->faceAngle[1];
        switch (rider->action) {
	    case ACT_RIDE_YOSHI_IDLE:
		cur_obj_init_animation_with_accel_and_sound(0, 1.0f);
		break;
	    case ACT_RIDE_YOSHI_WALK:
		cur_obj_init_animation_with_accel_and_sound(1, ABS(rider->forwardVel) / 8.0f);
		if (animFrame == 0 || animFrame == 15) cur_obj_play_sound_2(SOUND_GENERAL_YOSHI_WALK);
		break;
	    case ACT_RIDE_YOSHI_JUMP:
		cur_obj_init_animation(2);
		if (o->header.gfx.animInfo.animFrame >= 3) o->header.gfx.animInfo.animFrame = 3;
		break;
	    case ACT_RIDE_YOSHI_FALL:
		if (rider->actionArg == 0) {
		    cur_obj_init_animation(2);
		    if (o->header.gfx.animInfo.animFrame >= 3) o->header.gfx.animInfo.animFrame = 3;
		} else if (rider->actionArg == 1) {
		    cur_obj_init_animation_with_accel_and_sound(1, 1.0f);
		}
		break;
	    case ACT_RIDE_YOSHI_FLUTTER:
		cur_obj_init_animation_with_accel_and_sound(1, 5.0f);
		if ((animFrame == 0) || (animFrame == 15)) play_sound(SOUND_GENERAL_YOSHI_FLUTTER_SHORT, o->header.gfx.cameraToObject);
		break;
	    default:
		mario_stop_riding_object(rider);
		break;
	}
	if (o->oInteractStatus & INT_STATUS_STOP_RIDING) {
	    o->heldByPlayerIndex = 0;
            o->oAction = 0;
            o->oInteractStatus = 0;
	}
    }
}
