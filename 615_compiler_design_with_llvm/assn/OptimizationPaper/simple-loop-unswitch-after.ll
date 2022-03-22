; ModuleID = 'simple-loop-unswitch-before.ll'
source_filename = "simple-loop-unswitch.c"
target datalayout = "e-m:e-p270:32:32-p271:32:32-p272:64:64-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-unknown-linux-gnu"

; Function Attrs: nounwind uwtable
define dso_local i32 @main() #0 {
  %1 = alloca i32, align 4
  %2 = alloca i32, align 4
  %3 = alloca i32, align 4
  %4 = alloca i32, align 4
  %5 = alloca i32, align 4
  store i32 0, i32* %1, align 4
  %6 = bitcast i32* %2 to i8*
  call void @llvm.lifetime.start.p0i8(i64 4, i8* %6) #2
  store i32 0, i32* %2, align 4, !tbaa !3
  %7 = bitcast i32* %3 to i8*
  call void @llvm.lifetime.start.p0i8(i64 4, i8* %7) #2
  store i32 10, i32* %3, align 4, !tbaa !3
  %8 = bitcast i32* %4 to i8*
  call void @llvm.lifetime.start.p0i8(i64 4, i8* %8) #2
  store i32 0, i32* %4, align 4, !tbaa !3
  %9 = bitcast i32* %5 to i8*
  call void @llvm.lifetime.start.p0i8(i64 4, i8* %9) #2
  store i32 0, i32* %5, align 4, !tbaa !3
  %10 = load i32, i32* %3, align 4
  %11 = icmp eq i32 %10, 10
  %.promoted = load i32, i32* %2, align 4, !tbaa !3
  %.promoted1 = load i32, i32* %5, align 4, !tbaa !3
  %.promoted3 = load i32, i32* %4, align 4, !tbaa !3
  br label %12

12:                                               ; preds = %22, %0
  %13 = phi i32 [ %23, %22 ], [ %.promoted3, %0 ]
  %14 = phi i32 [ %24, %22 ], [ %.promoted1, %0 ]
  %15 = phi i32 [ %25, %22 ], [ %.promoted, %0 ]
  %16 = icmp slt i32 %15, 10
  br i1 %16, label %17, label %26

17:                                               ; preds = %12
  br i1 %11, label %18, label %20

18:                                               ; preds = %17
  %19 = add nsw i32 %13, 1
  br label %22

20:                                               ; preds = %17
  %21 = add nsw i32 %14, 1
  br label %22

22:                                               ; preds = %20, %18
  %23 = phi i32 [ %13, %20 ], [ %19, %18 ]
  %24 = phi i32 [ %21, %20 ], [ %14, %18 ]
  %25 = add nsw i32 %15, 1
  br label %12, !llvm.loop !7

26:                                               ; preds = %12
  %.lcssa4 = phi i32 [ %13, %12 ]
  %.lcssa2 = phi i32 [ %14, %12 ]
  %.lcssa = phi i32 [ %15, %12 ]
  store i32 %.lcssa, i32* %2, align 4, !tbaa !3
  store i32 %.lcssa2, i32* %5, align 4, !tbaa !3
  store i32 %.lcssa4, i32* %4, align 4, !tbaa !3
  %27 = load i32, i32* %4, align 4, !tbaa !3
  %28 = bitcast i32* %5 to i8*
  call void @llvm.lifetime.end.p0i8(i64 4, i8* %28) #2
  %29 = bitcast i32* %4 to i8*
  call void @llvm.lifetime.end.p0i8(i64 4, i8* %29) #2
  %30 = bitcast i32* %3 to i8*
  call void @llvm.lifetime.end.p0i8(i64 4, i8* %30) #2
  %31 = bitcast i32* %2 to i8*
  call void @llvm.lifetime.end.p0i8(i64 4, i8* %31) #2
  ret i32 %27
}

; Function Attrs: argmemonly nofree nosync nounwind willreturn
declare void @llvm.lifetime.start.p0i8(i64 immarg, i8* nocapture) #1

; Function Attrs: argmemonly nofree nosync nounwind willreturn
declare void @llvm.lifetime.end.p0i8(i64 immarg, i8* nocapture) #1

attributes #0 = { nounwind uwtable "frame-pointer"="none" "min-legal-vector-width"="0" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "tune-cpu"="generic" }
attributes #1 = { argmemonly nofree nosync nounwind willreturn }
attributes #2 = { nounwind }

!llvm.module.flags = !{!0, !1}
!llvm.ident = !{!2}

!0 = !{i32 1, !"wchar_size", i32 4}
!1 = !{i32 7, !"uwtable", i32 1}
!2 = !{!"clang version 13.0.1"}
!3 = !{!4, !4, i64 0}
!4 = !{!"int", !5, i64 0}
!5 = !{!"omnipotent char", !6, i64 0}
!6 = !{!"Simple C/C++ TBAA"}
!7 = distinct !{!7, !8, !9}
!8 = !{!"llvm.loop.mustprogress"}
!9 = !{!"llvm.loop.unroll.disable"}
